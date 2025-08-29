#ifndef VOLTAGE_FPE_H
#define VOLTAGE_FPE_H

#include "veapi.h"
#include "vefpe.h"

typedef struct {
    VeLibCtx libctx;
    VeFPE fpeProtect;
    VeFPE fpeAccess;
} VoltageFPEContext;

VoltageFPEContext* CreateVoltageFPEContext(
    const char* policyURL,
    const char* trustStorePath,
    const char* cachePath,
    const char* identity,
    const char* sharedSecret,
    const char* format
);

char* VoltageProtect(VoltageFPEContext* ctx, const char* input);
char* VoltageAccess(VoltageFPEContext* ctx, const char* ciphertext);
void DestroyVoltageFPEContext(VoltageFPEContext* ctx);

#endif // VOLTAGE_FPE_H