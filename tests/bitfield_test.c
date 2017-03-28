#include <stdio.h>
#include <endian.h>
#include <assert.h>

#include "Implementation.h"
#include "TpmTypes.h"
#include "Tpm.h"
#include "Global.h"

#pragma GCC diagnostic ignored "-Wstrict-aliasing"

int main(void)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    const char *endian = "little";
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
    const char *endian = "big";
#endif

    TPMA_ALGORITHM tpmaa = {0};
    TPMA_OBJECT tpmao = {0};
    TPMA_SESSION tpmas = {0};
    TPMA_LOCALITY tpmal = {0};
    TPMA_PERMANENT tpmap = {0};
    TPMA_STARTUP_CLEAR tpmasc = {0};
    TPMA_MEMORY tpmam = {0};
    TPMA_CC tpmacc = {0};
    TPMA_MODES tpmamodes = {0};
    TPMA_NV tpmanv = {0};
    OBJECT_ATTRIBUTES oa = {0};
    SESSION_ATTRIBUTES sa = {0};
    int ret = 0;

    printf("This is a %s machine.\n", endian);

    tpmaa.object =  1;
    assert(sizeof(tpmaa) == 4);
    if (!( *((UINT32*)&tpmaa) & TPMA_ALGORITHM_OBJECT)) {
        printf("TPMA_ALGORITHM structure is badly defined.\n");
        ret = 1;
    }

    tpmao.fixedParent = 1;
    assert(sizeof(tpmao) == 4);
    if (!( *((UINT32*)&tpmao) & TPMA_OBJECT_FIXEDPARENT)) {
        printf("TPMA_OBJECT_FIXEDPARENT structure is badly defined.\n");
        ret = 1;
    }

    tpmas.auditReset = 1;
    assert(sizeof(tpmas) == 4);
    if (!( tpmas.val & TPMA_SESSION_AUDITRESET)) {
        printf("TPMA_SESSION structure is badly defined.\n");
        ret = 1;
    }

    tpmal.TPM_LOC_FOUR = 1;
    assert(sizeof(tpmal) == 4);
    if (!( tpmal.val  & (1 << 4))) {
        printf("TPMA_LOCALITY structure is badly defined.\n");
        ret = 1;
    }

    tpmap.disableClear = 1;
    assert(sizeof(tpmap) == 4);
    if (!( *((UINT32*)&tpmap) & (1 << 8))) {
        printf("TPMA_PERMANENT structure is badly defined.\n");
        ret = 1;
    }

    tpmasc.orderly = 1;
    tpmasc.phEnableNV = 1;
    assert(sizeof(tpmasc) == 4);
    if (!( *((UINT32*)&tpmasc) & (1 << 3 | 1 << 31))) {
        printf("TPMA_STARTUP_CLEAR structure is badly defined.\n");
        ret = 1;
    }

    tpmam.objectCopiedToRam = 1;
    assert(sizeof(tpmam) == 4);
    if (!( *((UINT32*)&tpmam) & (1 << 2))) {
        printf("TPMA_MEMORY structure is badly defined.\n");
        ret = 1;
    }

    tpmacc.flushed = 1;
    assert(sizeof(tpmacc) == 4);
    if (!( *((UINT32*)&tpmacc) & (1 << 24))) {
        printf("TPMA_CC structure is badly defined.\n");
        ret = 1;
    }

    tpmamodes.FIPS_140_2 = 1;
    assert(sizeof(tpmamodes) == 4);
    if (!( *((UINT32*)&tpmamodes) & (1 << 0))) {
        printf("TPMA_MODES structure is badly defined.\n");
        ret = 1;
    }

    tpmanv.TPMA_NV_GLOBALLOCK = 1;
    assert(sizeof(tpmanv) == 4);
    if (!( *((UINT32*)&tpmanv) & TPMA_NVA_GLOBALLOCK)) {
        printf("TPMA_NV structure is badly defined.\n");
        ret = 1;
    }

    oa.primary = 1;
    assert(sizeof(oa) == 4);
    if (!( *((UINT32*)&oa) & (1 << 5))) {
        printf("OBJECT_ATTRIBUTES structure is badly defined.\n");
        ret = 1;
    }

    sa.isPasswordNeeded = 1;
    assert(sizeof(sa) == 4);
    if (!( *((UINT32*)&sa) & (1 << 5))) {
        printf("SESSION_ATTRIBUTES structure is badly defined.\n");
        ret = 1;
    }

    if (ret) {
        printf("There were errors in the tests.\n");
    } else {
        printf("All tests passed.\n");
    }

    return ret;
}
