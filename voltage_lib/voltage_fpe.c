#include <stdlib.h>
#include <string.h>
#include "voltage_fpe.h"
#include "veapi.h"
#include "vefpe.h"

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