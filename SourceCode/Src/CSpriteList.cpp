#include "CSpriteList.h"

CSpriteList::CSpriteList()
{
    //ctor
    m_pListHeader = NULL;
    m_iListSize = 0;
}

int CSpriteList::GetListSize()
{
    return m_iListSize;
}

// ���һ��Sprite��������
SpriteStruct *CSpriteList::AddSprite( CSprite *pSprite )
{
	if( NULL == pSprite )
		return NULL;
	SpriteStruct	*pPtr	=	new SpriteStruct;
	pPtr->pSprite	=	pSprite;
	pPtr->pNext		=	NULL;
	pPtr->pPrev		=	NULL;
	// ���������β
	if( NULL == m_pListHeader )
		m_pListHeader	=	pPtr;
	else
	{
		SpriteStruct	*pTemp	=	m_pListHeader;
		while( NULL != pTemp->pNext )
			pTemp	=	pTemp->pNext;
		pPtr->pPrev		=	pTemp;
		pTemp->pNext	=	pPtr;
	}
	m_iListSize++;
	return pPtr;
}

void CSpriteList::DeleteSprite( const char *szName, bool bDeleteImage )
{
	SpriteStruct	*pPtr	=	NULL;
	for( pPtr	=	m_pListHeader; NULL != pPtr; pPtr	=	pPtr->pNext )
	{
		if( strcmp( szName, pPtr->pSprite->GetName() ) == 0 )
		{
			// ����ָ���������ȡ��(���������е�ǰ��ָ������ָ��)
			// ����Ŀǰ�������£���ABC����ֵ��A <-> B <-> C����Ҫɾ��B
			// ����Ҫ��A��Nextָ��C��C��Prevָ��A��ɾ������ΪA <->C
			if( NULL != pPtr->pNext )
			{
				pPtr->pNext->pPrev	=	pPtr->pPrev;
			}
			if( NULL != pPtr->pPrev )
			{
				pPtr->pPrev->pNext	=	pPtr->pNext;
			}
			// ����Ǳ�ͷ
			if( pPtr == m_pListHeader )
			{
				m_pListHeader	=	m_pListHeader->pNext;
			}
			// ɾ��Sprite
			if( bDeleteImage )
				pPtr->pSprite->DeleteSprite();
			// �ͷ��ڴ�
			delete pPtr;
			m_iListSize--;
			return;
		}
	}
}

void CSpriteList::DeleteSprite( CSprite *pSprite, bool bDeleteImage )
{
	SpriteStruct	*pPtr	=	NULL;
	for( pPtr	=	m_pListHeader; NULL != pPtr; pPtr	=	pPtr->pNext )
	{
		if( pPtr->pSprite == pSprite )
		{
			if( NULL != pPtr->pNext )
			{
				pPtr->pNext->pPrev	=	pPtr->pPrev;
			}
			if( NULL != pPtr->pPrev )
			{
				pPtr->pPrev->pNext	=	pPtr->pNext;
			}
			if( pPtr == m_pListHeader )
			{
				m_pListHeader	=	m_pListHeader->pNext;
			}
			if( bDeleteImage )
				pPtr->pSprite->DeleteSprite();
			delete pPtr;
			m_iListSize--;
			return;
		}
	}
}

void CSpriteList::DeleteAllSprite( bool bDeleteImage )
{
	SpriteStruct	*pPtr				=	NULL;
	SpriteStruct	*pPtrhNext	=	m_pListHeader;
	while( NULL != pPtrhNext )
	{
		pPtr			=	pPtrhNext;
		pPtrhNext	=	pPtrhNext->pNext;
		if( bDeleteImage )
			pPtr->pSprite->DeleteSprite();
		delete pPtr;
	};
	m_pListHeader	=	NULL;
	m_iListSize		=	0;
}

CSprite *CSpriteList::GetSprite( const int iIndex )
{
			int				iLoop	=	0;
			SpriteStruct	*pPtr	=	m_pListHeader;
			while( NULL != pPtr )
			{
				if( iLoop == iIndex )
					return pPtr->pSprite;
				iLoop++;
				pPtr	=	pPtr->pNext;
			}
			return NULL;
}

CSprite* CSpriteList::GetSprite( const char *szName )
{
	SpriteStruct	*pPtr	=	m_pListHeader;
	while( NULL != pPtr )
	{
		if( strcmp( pPtr->pSprite->GetName(), szName ) == 0 )
			return pPtr->pSprite;
		pPtr	=	pPtr->pNext;
	}
	return NULL;
}

CSpriteList::~CSpriteList()
{
    //dtor
}
