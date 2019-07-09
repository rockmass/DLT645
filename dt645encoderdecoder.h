#ifndef DT645ENCODERDECODER_H
#define DT645ENCODERDECODER_H

#include <QObject>
#include <QtCore>

#include "meterplugintypes.h"
#include "dlt645defines.h"


///[!] meter-plugin-shared
#include "shared/meterpluginhelper.h"


#define DEF_TARIFF_NUMB     2
#define DEF_THREE_PHASE     true
#define DEF_ONLY_ACTIVE     false


class DT645EncoderDecoder : public QObject
{
    Q_OBJECT
public:
    explicit DT645EncoderDecoder(QObject *parent = nullptr);

    bool verboseMode;
    QByteArray lastAddr;//DLT645 mode = 45230100
    bool lastWas1997format;

    struct MessageValidatorResult
    {
        QList<quint8> listMeterMess;
        quint32 commandCode;//contains ERR byte from a payload
        quint8 errCode;//from a control byte
        QString errstr;

        bool isValid;

        MessageValidatorResult() : commandCode(0), errCode(0), isValid(false) {}
    };

    static QByteArray bcdList2normal(const QList<quint8> &list);

    static QByteArray bcd2normal(const QByteArray &bcd);

    static QByteArray arr2bcd(const QByteArray &arr);

    static QByteArray arrRotate(const QByteArray &in);
    static QByteArray arrRotateExt(const quint64 &number, const int &maxHexLen, const qint8 &addbyte);
    static QByteArray arrRotateExt(const QByteArray &in, const qint8 &addbyte);


    static QByteArray getBroadcastAddr();

    static QByteArray getNormalMeterAddress(const QByteArray &ni);

    static QString enableDisableTheEnergyKey(const QString &oldvrsn, const QString &energy, const bool &isSupported);


    static QStringList getSupportedEnrg(const quint8 &code, const QString &version);

    static bool isPollCodeSupported(const quint16 &pollCode, QVariantHash &hashTmpData);

    static bool isPollCodeSupported(const quint16 &pollCode);

    static bool is1997version(const QString &version);

    static QByteArray defPassword4meterVersion(const QString &version);

    static QByteArray defPassword4meterVersion(const bool &is1997);

    static QBitArray getBitarrFromAbyteERR(const quint32 &errcode);

    static bool hasNoData(const quint32 &errcode);

    static QString calcMeterAddr(const QString &meterSn);

    void insertDefaultHashMessageValues(QVariantHash &hashMessage);


    QByteArray createAmessage(const QByteArray &ni, const quint8 &controlcode, const quint16 &command, const QByteArray &payload);

    QByteArray getMeterAddress(const QByteArray &ni);

    QByteArray calcByteModulo(const QByteArray &messagepart);

    QByteArray getReadMessage(const QByteArray &ni, const quint16 &command);

    QByteArray getReadMessage(const QVariantHash &hashConstData, const quint16 &command);




    bool checkMessageBytes(const QByteArray &readArr, const QByteArray &lastAddr, const int &indxfrom, const QList<quint8> &bytes, const bool &toSlave, quint8 &errCode, QString &errstr, QByteArray &destination);

    quint32 getCommandFromAmessage(const QList<quint8> &bytes, const bool &hasAnError);


    MessageValidatorResult messageIsValid(const QByteArray &readArr, const QByteArray &lastAddr);

    MessageValidatorResult messageIsValidExt(const QByteArray &readArr, const QByteArray &lastAddr, const bool &toSlave, QByteArray &destination);


    Mess2meterRezult mess2meter(const Mess2meterArgs &pairAboutMeter);

    QVariantHash decodeMeterData(const DecodeMeterMess &threeHash);


    bool decodeMeterSN(const MessageValidatorResult &decoderesult, QVariantHash &hashTmpData);

    bool decodeMeterDate(const MessageValidatorResult &decoderesult, QVariantHash &hashTmpData);

    bool decodeMeterTime(const MessageValidatorResult &decoderesult, const QVariantHash &hashConstData, QVariantHash &hashTmpData, ErrCounters &warnerr, bool &getDateAgain, bool &stopPoll);

    //    void preparyMeterJournal(const QVariantHash &hashConstData, QVariantHash &hashTmpData, QVariantHash &hashMessage, quint16 &step);

//    QVariantHash fullMeterJrnl(const QList<quint8> &listMeterMess, const quint32 &commandCode, const quint8 &errCode,
//                           const QVariantHash &hashConstData, const QVariantHash &hashTmpData, quint16 &step, ErrCounters &warnerr);


    QVariantHash preparyVoltage(const QVariantHash &hashConstData, QVariantHash &hashTmpData, quint16 &step);

    QVariantHash fullVoltage(const MessageValidatorResult &decoderesult,
                           const QVariantHash &hashConstData, const QVariantHash &hashTmpData, quint16 &step, ErrCounters &warnerr);


    QVariantHash preparyPower(const QVariantHash &hashConstData, QVariantHash &hashTmpData, quint16 &step);

    QVariantHash fullPower(const MessageValidatorResult &decoderesult,
                           const QVariantHash &hashConstData, const QVariantHash &hashTmpData, quint16 &step, ErrCounters &warnerr);


    QVariantHash preparyTotalEnrg(const QVariantHash &hashConstData, QVariantHash &hashTmpData);

    QVariantHash fullTotalEnrg(const MessageValidatorResult &decoderesult,
                           const QVariantHash &hashConstData, const QVariantHash &hashTmpData, quint16 &step, ErrCounters &warnerr);


//    void preparyEoD(const QVariantHash &hashConstData, QVariantHash &hashTmpData, QVariantHash &hashMessage, quint16 &step);

//    QVariantHash fullEoD(const QList<quint8> &listMeterMess, const quint32 &commandCode, const quint8 &errCode,
//                           const QVariantHash &hashConstData, const QVariantHash &hashTmpData, quint16 &step, ErrCounters &warnerr);


    QVariantHash preparyEoM(const QVariantHash &hashConstData, QVariantHash &hashTmpData, quint16 &step);

    QVariantHash fullEoM(const MessageValidatorResult &decoderesult,
                           const QVariantHash &hashConstData, const QVariantHash &hashTmpData, quint16 &step, ErrCounters &warnerr);

    void insertNotSupValues2hash(const QString &prefics, const QString &enrg, const int &trffs, QVariantHash &hash);

    void insertStatuses2hash(const QString &prefics, const QString &enrg, const int &trffs, const QString &stts, QVariantHash &hash);

signals:

public slots:
};

#endif // DT645ENCODERDECODER_H
