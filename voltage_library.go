package main

/*
#cgo CFLAGS: -I./voltage_lib
#cgo LDFLAGS: -L./voltage_lib -lvoltagefpe -lvibesimpledyn -lpthread -Wl,-rpath=./voltage_lib
#include "voltage_fpe.h"
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
