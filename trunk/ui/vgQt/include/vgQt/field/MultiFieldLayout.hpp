#ifndef _VGQT_FIELD_MULTIFIELDLAYOUT_HPP_
#define _VGQT_FIELD_MULTIFIELDLAYOUT_HPP_

#include <QGridLayout>

/**
 * @brief	Implements a MultiFieldLayout with a custom signal
 */
class MultiFieldLayout : public QGridLayout
{
    Q_OBJECT

Q_SIGNALS:
    void signalChanged();
};

#endif // _VGQT_FIELD_MULTIFIELDLAYOUT_HPP_
