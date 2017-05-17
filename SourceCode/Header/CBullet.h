#ifndef CBULLET_H
#define CBULLET_H

#include <CommonClass.h>
#include "CGameSprite.h"

class CBullet : public CGameSprite
{
    public:
        CBullet(const int iType,const int iSize, const char *szName);

        bool IsMyBullet();
        void OnColOtherSprite( CGameSprite *pOther );
        bool IsBullet();
        int GetSize();

        virtual ~CBullet();
    protected:
    private:
        int	m_iType;
        int m_iSize;

};

#endif // CBULLET_H
