#pragma once

void removeDups(char* pSTR)
{
	if (pSTR == nullptr) return;

	char* tmp = pSTR;

	while (*pSTR != '\0')
	{
		if (*pSTR != *(pSTR + 1))
		{
			*(tmp++) = *pSTR;
		}
		pSTR++;
	}
	*tmp = '\0';
}
