

#ifndef _SEEK_BAR_LISTENER_
#define _SEEK_BAR_LISTENER_


class SeekBarListener
{
public:
    virtual void SeekStart(float progress)=0;
    virtual void SeekMove(float progress)=0;
	virtual void SeekEnd(float progress)=0;
};



#endif
