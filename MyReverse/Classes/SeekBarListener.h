/**
 * @brief シークバーを実装するクラスのインターフェース
 * @author 畑祐輔
 *
 */


#ifndef __SEEK_BAR_LISTENER_H__
#define __SEEK_BAR_LISTENER_H__


class SeekBarListener
{
public:
    /**
     * シークバーをタッチした際呼ばれる
     * @param progress シークバーのメモリ位置(0 ~ 1.0)
     * @param tag シークバーのタグ
     */
    virtual void SeekStart(float progress,int tag)=0;
    virtual void SeekMove(float progress,int tag)=0;
	virtual void SeekEnd(float progress,int tag)=0;
};



#endif
