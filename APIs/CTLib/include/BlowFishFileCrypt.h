// claudio

#pragma once

#include ".\BlowFish.h"

class CTLIB CBlowFishFileCrypt
{
public:
	CBlowFishFileCrypt(int defaultKey = 0);
	virtual ~CBlowFishFileCrypt(void);

/////// 
protected:
	char	m_Cypher[CRYPT_KEY_LENGTH]; // the algorithm key cypher, must be the same for crypt / decrypt

/////// 
public:
	BOOL	DoCrypt(const char* filePathIn, const char* filePathOut); 
	BOOL	DoCrypt(char* pFromMemory, int fromSize, char* pToMemory, int toSize); 
	BOOL	DoCrypt(const char* filePathIn, char* pToMemory, int toSize); 
	BOOL	DoCrypt(char* pFromMemory, int fromSize, const char* filePathOut); 

	BOOL	DoDecrypt(const char* filePathIn, const char* filePathOut); 
	BOOL	DoDecrypt(char* pFromMemory, int fromSize, char* pToMemory, int toSize); 
	BOOL	DoDecrypt(const char* filePathIn, char* pToMemory, int toSize); 
	BOOL	DoDecrypt(char* pFromMemory, int fromSize, const char* filePathOut); 

	void	SetDefaultKey(int iKey);
	void	SetCustomKey(const char* customKey);
	int		GetPairBufferSize(int curBufferSize);

private:
	void	PrepareCypher(const char* key);
	
	BOOL	BlowFish(BOOL bCrypt, char* cypher, const char* filePathIn, const char* filePathOut); // BOOL bCrypt = TRUE / FALSE (crypt/decrypt)
	BOOL	BlowFishInMem(BOOL bCrypt, char* cypher, char* pFromMemory, int fromSize, char* pToMemory, int toSize); // BOOL bCrypt = TRUE / FALSE (crypt/decrypt)
	BOOL	BlowFishInMem(BOOL bCrypt, char* cypher, char* pFromMemory, int fromSize, const char* filePathOut); // BOOL bCrypt = TRUE / FALSE (crypt/decrypt)
	BOOL	BlowFishInMem(BOOL bCrypt, char* cypher, const char* filePathIn, char* pToMemory, int toSize);// BOOL bCrypt = TRUE / FALSE (crypt/decrypt)
};
