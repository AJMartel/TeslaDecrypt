/*
 *  Copyright (C) 2015 Cisco Talos Security Intelligence and Research Group
 *
 *  Authors: Andrea Allievi and Emmanuel Tacheau
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 * 
 *	Filename: TeslaDecrypter.h
 *	Defines the CTeslaDecrypter class
 *	Last revision: 04/17/2015
 *
 */
#pragma once
#include "Log.h"

#include "resource.h"

// Tesla Decrypter class
class CTeslaDecrypter
{
public:
	// Default constructor
	CTeslaDecrypter(CLog * pLog = NULL);

	// Default destructor
	~CTeslaDecrypter(void);

	// Set if to keep the original files or not
	bool KeepOriginalFiles(bool bValue) { g_bKeepOriginalFiles = bValue; return true; }

	// Set whether or not to delete the TEslaCrypt garbage files
	bool DeleteTeslaCryptGarbage(bool bValue) { g_bCleanupTeslaFiles = bValue; return true; }

	// Read the "key.dat" file and obtain the Master Key
	bool ReadKeyFile(LPTSTR fileName, BOOLEAN * pbMasterKeyStripped = NULL);

	// Manually set the master key
	bool SetMasterKey(BYTE key[32]); 

	// Decrypt a TeslaLocker encryped file
	bool DecryptTeslaFile(LPTSTR orgFile, LPTSTR destFile = NULL);

	// Decrypt an entire directory, looking for a specific pattern
	bool DecryptDirectory(LPTSTR dirName, LPTSTR pattern = L"*.ecc", bool bRecursive = true, bool bStripExt = true, bool bIsRecursiveCall = false);

	// Decrypt the entire Workstation
	bool DecryptAllPcFiles(LPTSTR pattern = L"*.ecc");

	// Transform a buffer in printable hex bytes
	static LPTSTR BytesToHex(LPBYTE buff, DWORD buffSize, TCHAR delimChr = NULL);

	// Transform a printable hex bytes in a real byte stream
	static LPBYTE HexToBytes(LPTSTR hexString, DWORD strSize);

private:
	// Calculate the SHA256 of a target buffer
	bool GetSha256(LPBYTE lpBuff, DWORD dwSize, BYTE sha256[32]);

	// Decrypt / encrypt with and AES CBC 256 algorithm
	bool EncDecWithAes256(LPBYTE lpBuff, DWORD dwBuffSize, BYTE iv[16], LPBYTE * lppOut, LPDWORD lpdwOutBuffSize, bool bEncrypt = false);

private:
	// The shifted Master key (32 bytes)
	BYTE g_masterKey[32];

	// The SHA256 of the master Key (32 bytes)
	BYTE g_sha256mKey[32];

	// Set to TRUE if I have already obtained the master key
	bool g_bKeySet;

	// Set to TRUE if ìI have to keep the original encrypted files
	bool g_bKeepOriginalFiles;

	// This class instance Log
	CLog * g_pLog;

	// Set to TRUE if this instance has created the log
	bool g_bIsMyLog;				

	// Set to true if I have to delete all the TeslaCrypt garbage files
	bool g_bCleanupTeslaFiles;
};
