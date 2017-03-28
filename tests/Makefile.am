#
# tests/Makefile.am
#
# For the license, see the LICENSE file in the root directory.
#

check_PROGRAMS = base64decode

TESTS = base64decode.sh

SRCDIR = ../src

base64decode_CFLAGS = -I../include
base64decode_LDFLAGS = -ltpms -L../src/.libs

if WITH_TPM2

check_PROGRAMS += bitfield_test
TESTS += bitfield_test

bitfield_test_SOURCES = \
	bitfield_test.c

bitfield_test_CFLAGS = \
	-D_POSIX_ \
	-DTPM_POSIX \
	-I$(SRCDIR)/tpm2 \
	-I$(SRCDIR)/tpm2/crypto \
	-I$(SRCDIR)/tpm2/crypto/openssl

endif # WITH_TPM2

if LIBTPMS_USE_FREEBL

check_PROGRAMS += freebl_sha1flattensize
TESTS += freebl_sha1flattensize

endif

freebl_sha1flattensize_SOURCES = \
	freebl_sha1flattensize.c
freebl_sha1flattensize_CFLAGS = \
	$(shell nss-config --cflags) \
	$(shell nspr-config --cflags) \
	-Wall -Werror
freebl_sha1flattensize_LDFLAGS = \
	-lfreebl \
	$(shell nspr-config --libs) \
	$(shell nss-config --libs)

EXTRA_DIST = \
	freebl_sha1flattensize.c \
	base64decode.c \
	base64decode.sh
