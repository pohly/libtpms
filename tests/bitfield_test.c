#include <stdio.h>
#include <endian.h>
#include <assert.h>

#include "Implementation.h"
#include "TpmTypes.h"
#include "Tpm.h"
#include "Global.h"

#pragma GCC diagnostic ignored "-Wstrict-aliasing"

int check_bits(uint32_t value, uint32_t set_bits)
{
    if ((value & set_bits) != set_bits)
        return -1;
    if ((value & ~set_bits) != 0)
        return -1;
    return 0;
}

int main(void)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    const char *endian = "little";
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
    const char *endian = "big";
#endif

    TPMA_ALGORITHM tpmaa;
    TPMA_OBJECT tpmao;
    TPMA_SESSION tpmas;
    TPMA_LOCALITY tpmal;
    TPMA_PERMANENT tpmap;
    TPMA_STARTUP_CLEAR tpmasc;
    TPMA_MEMORY tpmam ;
    TPMA_CC tpmacc;
    TPMA_MODES tpmamodes;
    TPMA_NV tpmanv;
    OBJECT_ATTRIBUTES oa ;
    SESSION_ATTRIBUTES sa ;
    int ret = 0;

    printf("This is a %s machine.\n", endian);

#define TESTCASE(structure, field, value, bits, badstruct) \
    memset(&structure, 0, sizeof(structure)); \
    structure.field = value; \
    if (check_bits(*(UINT32*)&structure, bits) < 0) { \
        printf("%d: %s structure is badly defined (field " #field").\n", \
               __LINE__, badstruct); \
        ret = 1; \
    }

#define TESTCASE_VAL(structure, field, value, bits, badstruct) \
    memset(&structure, 0, sizeof(structure)); \
    structure.field = value; \
    if (check_bits(structure.val, bits) < 0) { \
        printf("%d: %s structure is badly defined (field " #field").\n", \
               __LINE__, badstruct); \
        ret = 1; \
    }

    assert(sizeof(tpmaa) == 4);
    TESTCASE(tpmaa, object, 1, TPMA_ALGORITHM_OBJECT, "TPMA_ALGORITHM")
    TESTCASE(tpmaa, signing, 1, TPMA_ALGORITHM_SIGNING, "TPMA_ALGORITHM")
    TESTCASE(tpmaa, method, 1, TPMA_ALGORITHM_METHOD, "TPMA_ALGORITHM")

    assert(sizeof(tpmao) == 4);
    TESTCASE(tpmao, fixedParent, 1, TPMA_OBJECT_FIXEDPARENT,
             "TPMA_OBJECT_FIXEDPARENT");
    TESTCASE(tpmao, adminWithPolicy, 1, TPMA_OBJECT_ADMINWITHPOLICY,
             "TPMA_OBJECT_FIXEDPARENT");
    TESTCASE(tpmao, decrypt, 1, TPMA_OBJECT_DECRYPT,
             "TPMA_OBJECT_FIXEDPARENT");

    assert(sizeof(tpmas) == 4);
    TESTCASE_VAL(tpmas, auditReset, 1, TPMA_SESSION_AUDITRESET,
             "TPMA_SESSION")
    TESTCASE_VAL(tpmas, audit, 1, TPMA_SESSION_AUDIT,
             "TPMA_SESSION")
    TESTCASE_VAL(tpmas, continueSession, 1, TPMA_SESSION_CONTINUESESSION,
             "TPMA_SESSION")

    assert(sizeof(tpmal) == 4);
    TESTCASE_VAL(tpmal, TPM_LOC_FOUR, 1, 1 << 4, "TPMA_LOCALITY")
    TESTCASE_VAL(tpmal, TPM_LOC_ZERO, 1, 1 << 0, "TPMA_LOCALITY")

    assert(sizeof(tpmap) == 4);
    TESTCASE(tpmap, disableClear, 1, 1 << 8, "TPMA_PERMANENT")

    assert(sizeof(tpmasc) == 4);
    TESTCASE(tpmasc, orderly, 1, 1 << 31, "TPMA_STARTUP_CLEAR")
    TESTCASE(tpmasc, phEnableNV, 1, 1 << 3, "TPMA_STARTUP_CLEAR")

    assert(sizeof(tpmam) == 4);
    TESTCASE(tpmam, objectCopiedToRam, 1, 1 << 2, "TPMA_MEMORY")
    TESTCASE(tpmam, sharedRAM, 1, 1 << 0, "TPMA_MEMORY")

    assert(sizeof(tpmacc) == 4);
    TESTCASE(tpmacc, flushed, 1, 1 << 24, "TPM_CC");
    TESTCASE(tpmacc, V, 1, 1 << 29, "TPM_CC");
    TESTCASE(tpmacc, Res, 1, 1 << 30, "TPM_CC");
    TESTCASE(tpmacc, Res, 2, 2 << 30, "TPM_CC");

    assert(sizeof(tpmamodes) == 4);
    TESTCASE(tpmamodes, FIPS_140_2, 1, 1 << 0, "TPMA_MODES");

    assert(sizeof(tpmanv) == 4);
    TESTCASE(tpmanv, TPMA_NV_GLOBALLOCK, 1, TPMA_NVA_GLOBALLOCK,
             "TPMA_NV");
    TESTCASE(tpmanv, TPMA_NV_NO_DA, 1, TPMA_NVA_NO_DA,
             "TPMA_NV");
    TESTCASE(tpmanv, TPMA_NV_PPREAD, 1, TPMA_NVA_PPREAD,
             "TPMA_NV");
    TESTCASE(tpmanv, TPMA_NV_AUTHWRITE, 1, TPMA_NVA_AUTHWRITE,
             "TPMA_NV");

    assert(sizeof(oa) == 4);
    TESTCASE(oa, publicOnly, 1, 1 << 0, "OBJECT_ATTRIBUTES");
    TESTCASE(oa, primary, 1, 1 << 5, "OBJECT_ATTRIBUTES");
    TESTCASE(oa, firstBlock, 1, 1 << 12, "OBJECT_ATTRIBUTES");
    TESTCASE(oa, occupied, 1, 1 << 15, "OBJECT_ATTRIBUTES");
    TESTCASE(oa, external, 1, 1 << 17, "OBJECT_ATTRIBUTES");

    assert(sizeof(sa) == 4);
    TESTCASE(sa, isPolicy, 1, 1 << 0, "SESSION_ATTRIBUTES");
    TESTCASE(sa, isPasswordNeeded, 1, 1 << 5, "SESSION_ATTRIBUTES");
    TESTCASE(sa, isLockoutBound, 1, 1 << 9, "SESSION_ATTRIBUTES");
    TESTCASE(sa, isTemplateSet, 1, 1 << 13, "SESSION_ATTRIBUTES");

    if (ret) {
        printf("There were errors in the tests.\n");
    } else {
        printf("All tests passed.\n");
    }

    return ret;
}
