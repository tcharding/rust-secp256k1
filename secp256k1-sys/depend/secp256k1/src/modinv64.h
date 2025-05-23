/***********************************************************************
 * Copyright (c) 2020 Peter Dettman                                    *
 * Distributed under the MIT software license, see the accompanying    *
 * file COPYING or https://www.opensource.org/licenses/mit-license.php.*
 **********************************************************************/

#ifndef SECP256K1_MODINV64_H
#define SECP256K1_MODINV64_H

#include "util.h"

#ifndef SECP256K1_WIDEMUL_INT128
#error "modinv64 requires 128-bit wide multiplication support"
#endif

/* A signed 62-bit limb representation of integers.
 *
 * Its value is sum(v[i] * 2^(62*i), i=0..4). */
typedef struct {
    int64_t v[5];
} rustsecp256k1_v0_11_modinv64_signed62;

typedef struct {
    /* The modulus in signed62 notation, must be odd and in [3, 2^256]. */
    rustsecp256k1_v0_11_modinv64_signed62 modulus;

    /* modulus^{-1} mod 2^62 */
    uint64_t modulus_inv62;
} rustsecp256k1_v0_11_modinv64_modinfo;

/* Replace x with its modular inverse mod modinfo->modulus. x must be in range [0, modulus).
 * If x is zero, the result will be zero as well. If not, the inverse must exist (i.e., the gcd of
 * x and modulus must be 1). These rules are automatically satisfied if the modulus is prime.
 *
 * On output, all of x's limbs will be in [0, 2^62).
 */
static void rustsecp256k1_v0_11_modinv64_var(rustsecp256k1_v0_11_modinv64_signed62 *x, const rustsecp256k1_v0_11_modinv64_modinfo *modinfo);

/* Same as rustsecp256k1_v0_11_modinv64_var, but constant time in x (not in the modulus). */
static void rustsecp256k1_v0_11_modinv64(rustsecp256k1_v0_11_modinv64_signed62 *x, const rustsecp256k1_v0_11_modinv64_modinfo *modinfo);

/* Compute the Jacobi symbol for (x | modinfo->modulus). x must be coprime with modulus (and thus
 * cannot be 0, as modulus >= 3). All limbs of x must be non-negative. Returns 0 if the result
 * cannot be computed. */
static int rustsecp256k1_v0_11_jacobi64_maybe_var(const rustsecp256k1_v0_11_modinv64_signed62 *x, const rustsecp256k1_v0_11_modinv64_modinfo *modinfo);

#endif /* SECP256K1_MODINV64_H */
