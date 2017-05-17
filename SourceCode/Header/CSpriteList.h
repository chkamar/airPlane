#ifndef CSPRITELIST_H
#define CSPRITELIST_H
#include "CommonClass.h"

struct	SpriteStruct
{
    CSprite	    *pSprite;
    SpriteStruct	*pNext;
    SpriteStruct	*pPrev;
};

class CSpriteList//保存敌方战机
{
    public:
        CSpriteList();

        int GetListSize();
        SpriteStruct *AddSprite( CSprite *pSprite );
        void DeleteSprite( const char *szName, bool bDeleteImage );
        void DeleteSprite( CSprite *pSprite, bool bDeleteImage );
        void DeleteAllSprite( bool bDeleteImage );
        CSprite* GetSprite( const int iIndex );
        CSprite* GetSprite( const char *szName );

        virtual ~CSpriteList();
    protected:
    private:
        SpriteStruct *m_pListHeader;
		int	 m_iListSize;
};

#endif // CSPRITELIST_H
