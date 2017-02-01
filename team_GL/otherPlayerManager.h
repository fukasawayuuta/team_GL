#pragma once
class COtherPlayerManager
{
public:
	COtherPlayerManager(void);
	~COtherPlayerManager(void);

	void Init(void);
	void Uninit(void);
	void Update( void );

	static COtherPlayerManager *Create(void);
	static void CopyRecvData(char *data) {strcpy(m_RecvData, data);}

private:
	COtherPlayer *m_OtherPlayer;
	static char m_RecvData[128];
};

