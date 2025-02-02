#ifndef ANALYZER_H
#define ANALYZER_H

#include <QObject>
#include <QDateTime>
#include "analyzer/nanovna_analyzer.h"
#include <math.h>
#include "analyzerparameters.h"

#include <analyzer/analyzerparameters.h>
#include <analyzer/updater/downloader.h>
#include <devinfo/redeviceinfo.h>
#include <updatedialog.h>
#include <crc32.h>

#ifdef NEW_CONNECTION
#include <analyzer/hid_analyzer.h>
#include <analyzer/com_analyzer.h>
#else
#include <analyzer/hidanalyzer.h>
#include <analyzer/comanalyzer.h>
#endif

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

class Analyzer : public QObject
{
    QMap<QString, QString> m_mapFullInfo;

    Q_OBJECT
public:
    explicit Analyzer(QObject *parent = nullptr);
    ~Analyzer();

    QString getModelString(void);
    quint32 getModel(void);
    void updateFirmware (QIODevice *fw);
    double getVersion() const;
    QString getVersionString() const;
    QString getRevision() const;
    bool checkFile(QString path);
    void closeComPort();
    void connectDevice();
    ReDeviceInfo::InterfaceType connectionType() { return m_connectionType; }
    void setIsMeasuring (bool _isMeasuring);

    void setContinuos(bool isContinuos)
    {
        m_isContinuos = isContinuos;
        if(m_comAnalyzer != nullptr)
        {
            m_comAnalyzer->setContinuos(isContinuos);
        }
        if(m_hidAnalyzer != nullptr)
        {
            m_hidAnalyzer->setContinuos(isContinuos);
        }
        if (m_NanovnaAnalyzer != nullptr)
        {
            m_NanovnaAnalyzer->setContinuos(isContinuos);
        }
    }

    bool isMeasuring (void) const { return m_isMeasuring;}
    bool isNanovna(void) const { return m_nanovnaAnalyzerFound;}

#ifdef NEW_CONNECTION
    HidAnalyzer* getHidAnalyzer() { return m_hidAnalyzer; }
    ComAnalyzer* getComAnalyzer() { return m_comAnalyzer; }
#else
    hidAnalyzer* getHidAnalyzer() { return m_hidAnalyzer; }
    comAnalyzer* getComAnalyzer() { return m_comAnalyzer; }
#endif
    NanovnaAnalyzer* getNanovnaAnalyzer() { return m_NanovnaAnalyzer; }

    void setComAnalyzerFound (bool found) {m_comAnalyzerFound = found;}
    void setHidAnalyzerFound (bool found) {m_hidAnalyzerFound = found;}
    void setNanovnaAnalyzerFound (bool found) {m_nanovnaAnalyzerFound = found;}

    ReDeviceInfo::InterfaceType analyzerType() {
        if (m_comAnalyzer != nullptr)
            return ReDeviceInfo::Serial;
        if (m_NanovnaAnalyzer != nullptr)
            return ReDeviceInfo::NANO;
        return ReDeviceInfo::HID;
    }

    QString getSerialNumber(void) const;
    int getDots() { return m_dotsNumber; }
    bool sendCommand(QString cmd);
    void setParseState(int _state); // analyzerparameters.h: enum parse{}
    int getParseState();

private:
//    void send (char* byte);
//    char read (void);
#ifdef NEW_CONNECTION
    HidAnalyzer* m_hidAnalyzer=nullptr;
    ComAnalyzer* m_comAnalyzer=nullptr;
    BaseAnalyzer* m_baseAnalyzer=nullptr;
#else
    hidAnalyzer* m_hidAnalyzer=nullptr;
    comAnalyzer* m_comAnalyzer=nullptr;
#endif
    NanovnaAnalyzer* m_NanovnaAnalyzer=nullptr;

    quint32 m_analyzerModel;
    bool m_comAnalyzerFound;
    bool m_hidAnalyzerFound;
    bool m_nanovnaAnalyzerFound;
    quint32 m_chartCounter;
    bool m_isMeasuring;
    bool m_isContinuos;
    quint32 m_dotsNumber;
    bool m_autoCheckUpdate;
    bool m_getAnalyzerData = false;
    ReDeviceInfo::InterfaceType m_connectionType = ReDeviceInfo::HID;

    Downloader *m_downloader;
    UpdateDialog *m_updateDialog;
    bool m_bManualUpdate = false;

    QByteArray  *m_pfw;
    qint32 m_INFOSIZE;
    const quint32 m_MAGICAA230Z;
    const quint32 m_MAGICHID;
    const quint32 m_INTERNALMAGICAA230Z;
    const quint32 m_MAGICAA30ZERO;

    volatile bool m_calibrationMode;

    //---------------------------------------

signals:
    void analyzerFound(QString);
    void analyzerDisconnected();
    void newData (rawData);
    void newUserData (rawData, UserData);
    void newUserDataHeader (QStringList);
    void newAnalyzerData (rawData);
    void newMeasurement(QString);
    void newMeasurement(QString, qint64 fqFrom, qint64 fqTo, qint32 dotsNumber);
    void continueMeasurement(qint64 fqFrom, qint64 fqTo, qint32 dotsNumber);
    void measurementComplete();
    void measurementCompleteNano();
    void analyzerDataStringArrived(QString);
    void analyzerScreenshotDataArrived(QByteArray);
    void screenshotComplete(void);
    void updatePercentChanged(qint32);
    void aa30bootFound();
    void aa30updateComplete();
    void signalMeasurementError();
    void showNotification(QString msg, QString url);
    void licensesList(QString& _licenses);
    void licenseRequest(QString& _request);
    void licenseApplyResult(QString& _result);
    void updateAutocalibrate5(int _dots, QString _msg);
    void stopAutocalibrate5();

public slots:
    void searchAnalyzer();
    void on_hidAnalyzerFound (quint32 analyzerNumber);
    void on_comAnalyzerFound (quint32 analyzerNumber);
    void on_nanovnaAnalyzerFound (QString name);
    void on_comAnalyzerDisconnected ();
    void on_hidAnalyzerDisconnected ();
    void on_nanovnaAnalyzerDisconnected ();
    void on_measure (qint64 fqFrom, qint64 fqTo, qint32 dotsNumber);
    void on_measureUser (qint64 fqFrom, qint64 fqTo, qint32 dotsNumber);
    void on_measureContinuous(qint64 fqFrom, qint64 fqTo, qint32 dotsNumber);
    void on_measureOneFq(QWidget* parent, qint64 fqFrom, qint32 dotsNumber);
    void on_newData(rawData _rawData);
    void on_newUserData(rawData,UserData);
    void on_newUserDataHeader(QStringList);
    void on_analyzerDataStringArrived(QString str);
    void on_stopMeasuring();
    void on_itemDoubleClick(QString number, QString dotsNumber, QString name);
    void on_dialogClosed();
    void getAnalyzerData();
    void closeAnalyzerData();
    void on_analyzerScreenshotDataArrived(QByteArray arr);
    void on_screenshotComplete(void);
    void makeScreenshot();
    void on_updatePercentChanged(int number);
    void on_statisticsComplete();
    void on_downloadInfoComplete();
    void on_downloadFileComplete();
    void on_checkUpdatesBtn_clicked();
    void checkFirmwareUpdate();
    void setAutoCheckUpdate( bool state);
    void readFile(QString pathToFw);
    void on_internetUpdate();
    void on_progress(qint64 downloaded,qint64 total);
    void on_measureCalib(int dotsNumber);
    void setCalibrationMode(bool enabled);
    void on_stopMeasure();
    void slotFullInfo(QString str);
    bool needCheckForUpdate();

    void on_getLicenses();
    void on_generateLicence();
    void on_applyLicense(QString& _license);

    void on_connectNanoNVA(QString port);
    void on_disconnectNanoNVA();
    void on_connectSerial(QString port);
    void on_disconnectSerial();
    void on_connectBluetooth(QString port);
    void on_disconnectBluetooth();
    void on_connectHid();
    void on_disconnectHid();
    void on_disconnectDevice();

    void applyAnalyzer();
};

#endif // ANALYZER_H
