/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include "CMyFighter.h"
#include "CommonClass.h"
#include "CSpriteList.h"
/////////////////////////////////////////////////////////////////////////////////
//
// 游戏总管类。负责处理游戏主循环、游戏初始化、结束等工作
class	CGameMain
{
private:
	int				m_iGameState;				// 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中
    CMyFighter*     m_pMyFighter;
    CSprite*        g_BeginSprite;
    CTextSprite*    g_CurScoreText;
    CTextSprite*    g_MaxScoreText;
    int m_iCreatedSpriteCount;
    CSpriteList* m_SpriteList;
    int m_iMaxScore;
public:
	CGameMain();            //构造函数
	~CGameMain();           //析构函数

	// Get方法
	int				GetGameState()				{ return m_iGameState; }
    CMyFighter*     GetMyFighter()              { return m_pMyFighter; }
    CSpriteList*    GetM_SpriteList()              {return m_SpriteList;}
	// Set方法
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// 游戏主循环等
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();

	void	        OnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress );
	void            OnKeyUp( const int iKey );

    void            CreateBullet( int iType,int iEnemySize,const float fPosX, const float fPosY );
    void            AddSprite( CSprite *pSprite );
    void            DeleteSprite( CSprite *pSprite ,bool bDeleteImage);
    CGameSprite *   GetSprite( const int iIndex );
    CGameSprite *   GetSprite( const char *szName );
    bool            IsMyFighter( const char *szName );
    void            OnSpriteColSprite( const char *szSrcName, const char *szTarName );
    void            OnSpriteColWorldLimit( const char *szName, const int iColSide );
    bool            IsGameLost();
    void            SetCurScore(int score);
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
