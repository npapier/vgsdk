// VGSDK - Copyright (C) 2010, Nicolas Papier.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Nicolas Papier

#ifndef _VGPHYSFS_BLOWFISH_HPP
#define _VGPHYSFS_BLOWFISH_HPP

#include <Blowfish.h>
#include <string>
#include "vgPhysfs/vgPhysfs.hpp"



namespace vgPhysfs
{


/**
 * @brief Encryption interface
 *
 * @ingroup g_archCrypto
 */
struct VGPHYSFS_API IEncrypt
{
	virtual ~IEncrypt()=0 {}

	virtual void encrypt( unsigned char* buf, const size_t n )=0;
	virtual void encrypt( const unsigned char* in, unsigned char* out, const size_t n )=0;
};

/**
 * @brief Decryption interface
 *
 * @ingroup g_archCrypto
 */
struct VGPHYSFS_API IDecrypt
{
	virtual ~IDecrypt()=0 {}

	virtual void decrypt( unsigned char* buf, const size_t n )=0;
	virtual void decrypt( const unsigned char* in, unsigned char* out, const size_t n )=0;
};



/**
 * @brief Encryption and decryption of date using the Blowfish encryption algorithm.
 *
 * @see http://www.codeproject.com/KB/security/blowfish.aspx for implementation of Bruce Schneier's BLOWFISH algorithm from "Applied Cryptography", Second Edition.
 *
 * Blowfish is a block cipher that encrypts data in 8-byte blocks. The algorithm consists
 * of two parts: a key-expansion part and a data-encryption part. Key expansion converts a
 * variable key of at least 1 and at most 56 bytes into several subkey arrays totaling
 * 4168 bytes. Blowfish has 16 rounds. Each round consists of a key-dependent permutation,
 * and a key and data-dependent substitution. All operations are XORs and additions on 32-bit words.
 * The only additional operations are four indexed array data lookups per round.
 * Blowfish uses a large number of subkeys. These keys must be precomputed before any data
 * encryption or decryption. The P-array consists of 18 32-bit subkeys: P0, P1,...,P17.
 * There are also four 32-bit S-boxes with 256 entries each: S0,0, S0,1,...,S0,255;
 * S1,0, S1,1,...,S1,255; S2,0, S2,1,...,S2,255; S3,0, S3,1,...,S3,255;
 *
 * The Electronic Code Book (ECB), Cipher Block Chaining (CBC) and Cipher Feedback modes are used:
 *
 * In ECB mode if the same block is encrypted twice with the same key, the resulting
 * ciphertext blocks are the same.
 *
 * In CBC Mode a ciphertext block is obtained by first xoring the
 * plaintext block with the previous ciphertext block, and encrypting the resulting value.
 *
 * In CFB mode a ciphertext block is obtained by encrypting the previous ciphertext block
 * and xoring the resulting value with the plaintext
 *
 * The previous ciphertext block is usually stored in an Initialization Vector (IV).
 * An Initialization Vector of zero is commonly used for the first block, though other
 * arrangements are also in use.
 *
 * @ingroup g_archCrypto
 */
struct VGPHYSFS_API Blowfish : public IEncrypt, public IDecrypt
{
	//Constructor
	Blowfish( unsigned char* ucKey, const size_t n );
	Blowfish( const std::string key );

	// Encrypt/Decrypt Buffer in Place
	void encrypt( unsigned char* buf, const size_t n );
	void decrypt( unsigned char* buf, const size_t n );


	// Encrypt/Decrypt from Input Buffer to Output Buffer
	void encrypt( const unsigned char* in, unsigned char* out, const size_t n );
	void decrypt( const unsigned char* in, unsigned char* out, const size_t n );

private:
	CBlowFish m_blowfish;
};



} // namespace vgPhysfs

#endif // _VGPHYSFS_BLOWFISH_HPP
