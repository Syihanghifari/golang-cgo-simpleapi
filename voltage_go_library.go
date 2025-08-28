package main

/*
#cgo CFLAGS: -I./voltage_lib
#cgo LDFLAGS: -L./voltage_lib -Wl,-rpath=./voltage_lib -lvibesimpledyn -lpthread
#include <stdlib.h>
#include <string.h>
#include "veapi.h"
#include "vefpe.h"

// Structure to hold reusable context
typedef struct {
    VeLibCtx libctx;
    VeFPE fpeProtect;
    VeFPE fpeAccess;
} VoltageFPEContext;

// Create a Voltage context
VoltageFPEContext* CreateVoltageFPEContext(
    const char* policyURL,
    const char* trustStorePath,
    const char* cachePath,
    const char* identity,
    const char* sharedSecret,
    const char* format
) {
    VoltageFPEContext* ctx = (VoltageFPEContext*)malloc(sizeof(VoltageFPEContext));
    if (!ctx) return NULL;

    VeLibCtxParams args = VeLibCtxParamsDefaults;
    args.policyURL = policyURL;
    args.trustStorePath = trustStorePath;
    args.fileCachePath = cachePath;
    args.clientIdProduct = "VoltageCGO";
    args.clientIdProductVersion = "1.0";

    int status = VeCreateLibCtx(&args, &ctx->libctx);
    if (status != 0) return NULL;

    VeFPEParams fpeParams = VeFPEParamsDefaults;
    fpeParams.protect = 1;
    fpeParams.identity = identity;
    fpeParams.sharedSecret = sharedSecret;
    fpeParams.format = format;

    status = VeCreateFPE(ctx->libctx, &fpeParams, &ctx->fpeProtect);
    if (status != 0) return NULL;

    fpeParams.protect = 0;
    fpeParams.access = 1;

    status = VeCreateFPE(ctx->libctx, &fpeParams, &ctx->fpeAccess);
    if (status != 0) return NULL;

    return ctx;
}

char* VoltageProtect(VoltageFPEContext* ctx, const char* input) {
    VeProtectParams params = VeProtectParamsDefaults;
    static char ciphertextBuf[300];

    params.plaintext = (unsigned char*)input;
    params.plaintextSize = strlen(input);
    params.ciphertext = (unsigned char*)ciphertextBuf;
    params.ciphertextBufferSize = 300;

    int status = VeProtect(ctx->fpeProtect, &params);
    if (status != 0) return NULL;

    ciphertextBuf[params.ciphertextSize] = '\0';
    return strdup((char*)ciphertextBuf);
}

char* VoltageAccess(VoltageFPEContext* ctx, const char* ciphertext) {
    VeAccessParams params = VeAccessParamsDefaults;
    static char plaintextBuf[300];

    params.ciphertext = (unsigned char*)ciphertext;
    params.ciphertextSize = strlen(ciphertext);
    params.plaintext = (unsigned char*)plaintextBuf;
    params.plaintextBufferSize = 300;

    int status = VeAccess(ctx->fpeAccess, &params);
    if (status != 0) return NULL;

    plaintextBuf[params.plaintextSize] = '\0';
    return strdup((char*)plaintextBuf);
}

void DestroyVoltageFPEContext(VoltageFPEContext* ctx) {
    if (!ctx) return;
    VeDestroyFPE(&ctx->fpeProtect);
    VeDestroyFPE(&ctx->fpeAccess);
    VeDestroyLibCtx(&ctx->libctx);
    free(ctx);
}
*/
import "C"
import (
	"fmt"
	"sync"
)

type VoltageFPE struct {
	ctx *C.VoltageFPEContext
}

var (
	fpeStore     = make(map[string]*VoltageFPE)
	fpeStoreLock sync.RWMutex
)

func ExmapleUsingStaticFpe() {
	voltageURL := "https://voltage-pp-0000.opentext.co.id/policy/clientPolicy.xml"
	trustPath := "/opt/simple-api/trustStore-cloud"
	cachePath := "/opt/simple-api/cache"
	identity := "developer@ori.co.id"
	sharedSecret := "voltage123"
	format := "alphanumeric"

	fpe := NewVoltageFPE(
		voltageURL,
		trustPath,
		cachePath,
		identity,
		sharedSecret,
		format,
	)
	defer fpe.Close()

	plaintext := "12-10-2005 10:27:33"
	cipher := fpe.Protect(plaintext)
	recovered := fpe.Access(cipher)

	fmt.Println("Original: ", plaintext)
	fmt.Println("Cipher:   ", cipher)
	fmt.Println("Recovered:", recovered)
}

func ExampleUsingDynamicFpe() {
	voltageURL := "https://voltage-pp-0000.opentext.co.id/policy/clientPolicy.xml"
	trustPath := "/opt/simple-api/trustStore-cloud"
	cachePath := "/opt/simple-api/cache"
	RegisterFPE("fpe-dev", voltageURL, trustPath, cachePath, "developer@ori.co.id", "voltage123", "alphanumeric")

	cipher, _ := EncryptByID("fpe-dev", "12-10-2005 10:27:33")
	plain, _ := DecryptByID("fpe-dev", cipher)

	DeleteAllFPEs() // --> optional

	fmt.Println("Original: ", plain)
	fmt.Println("Cipher:   ", cipher)
}

func NewVoltageFPE(policyURL, trustPath, cachePath, identity, secret, format string) *VoltageFPE {
	cCtx := C.CreateVoltageFPEContext(
		C.CString(policyURL),
		C.CString(trustPath),
		C.CString(cachePath),
		C.CString(identity),
		C.CString(secret),
		C.CString(format),
	)
	if cCtx == nil {
		panic("failed to init Voltage FPE context")
	}
	return &VoltageFPE{ctx: cCtx}
}

func (v *VoltageFPE) Protect(data string) string {
	cStr := C.VoltageProtect(v.ctx, C.CString(data))
	return C.GoString(cStr)
}

func (v *VoltageFPE) Access(ciphertext string) string {
	cStr := C.VoltageAccess(v.ctx, C.CString(ciphertext))
	return C.GoString(cStr)
}

func (v *VoltageFPE) Close() {
	C.DestroyVoltageFPEContext(v.ctx)
}

func RegisterFPE(id, policyURL, trustPath, cachePath, identity, secret, format string) error {
	fpe := NewVoltageFPE(policyURL, trustPath, cachePath, identity, secret, format)

	fpeStoreLock.Lock()
	defer fpeStoreLock.Unlock()
	fpeStore[id] = fpe

	return nil
}

func DeleteAllFPEs() {
	fpeStoreLock.Lock()
	defer fpeStoreLock.Unlock()

	for _, fpe := range fpeStore {
		fpe.Close()
	}
	fpeStore = make(map[string]*VoltageFPE)
}

func EncryptByID(id, data string) (string, error) {
	fpeStoreLock.RLock()
	defer fpeStoreLock.RUnlock()

	fpe, ok := fpeStore[id]
	if !ok {
		return "", fmt.Errorf("FPE with id '%s' not found", id)
	}
	return fpe.Protect(data), nil
}

func DecryptByID(id, cipher string) (string, error) {
	fpeStoreLock.RLock()
	defer fpeStoreLock.RUnlock()

	fpe, ok := fpeStore[id]
	if !ok {
		return "", fmt.Errorf("FPE with id '%s' not found", id)
	}
	return fpe.Access(cipher), nil
}
