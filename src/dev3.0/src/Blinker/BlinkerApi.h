#ifndef BLINKER_API_H
#define BLINKER_API_H

#include <time.h>

#if defined(ESP8266) || defined(ESP32)
    #include <Ticker.h>
    #include <EEPROM.h>

    #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
        defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        #include "Blinker/BlinkerAuto.h"
    #endif

    #if defined(BLINKER_PRO)
        #include "Functions/BlinkerWlan.h"
    #endif
#endif

#if defined(ESP8266)
    #include <ESP8266HTTPClient.h>

    #if defined(BLINKER_WIFI)
        #include <WiFiClientSecure.h>

        static BearSSL::WiFiClientSecure client_s;
    #endif
    
#elif defined(ESP32)
    #include <HTTPClient.h>
#endif

#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
    #include "Blinker/BlinkerTimer.h"
    #include "Functions/BlinkerTimingTimer.h"
    #include "Functions/BlinkerOTA.h"
#endif

#if defined(BLINKER_AT_MQTT)
    #include "Blinker/BlinkerMQTTATBase.h"
#endif

#if defined(BLINKER_MQTT_AT)
    #include "Blinker/BlinkerATMASTER.h"
    #include "modules/ArduinoJson/ArduinoJson.h"
#endif

#include "Blinker/BlinkerApiBase.h"
#include "Blinker/BlinkerProtocol.h"

typedef BlinkerProtocol BProto;

enum b_joystickaxis_t {
    BLINKER_J_Xaxis,
    BLINKER_J_Yaxis
};

enum b_ahrsattitude_t {
    Yaw,
    Pitch,
    Roll
};

enum b_gps_t {
    LONG,
    LAT
};

enum b_rgb_t {
    BLINKER_R,
    BLINKER_G,
    BLINKER_B,
    BLINKER_BRIGHT
};

#if defined(BLINKER_PRO)
    enum BlinkerStatus
    {
        PRO_WLAN_CONNECTING,
        PRO_WLAN_CONNECTED,
        // PRO_WLAN_DISCONNECTED,
        PRO_WLAN_SMARTCONFIG_BEGIN,
        PRO_WLAN_SMARTCONFIG_DONE,
        PRO_DEV_AUTHCHECK_FAIL,
        PRO_DEV_AUTHCHECK_SUCCESS,
        PRO_DEV_REGISTER_FAIL,
        PRO_DEV_REGISTER_SUCCESS,
        PRO_DEV_INIT_SUCCESS,
        PRO_DEV_CONNECTING,
        PRO_DEV_CONNECTED,
        PRO_DEV_DISCONNECTED
    };
#endif

class BlinkerApi : public BlinkerProtocol
{
    public :
        void run();

        template <typename T>
        void print(T n);
        void print();
        
        template <typename T>
        void println(T n)   { print(n); }
        void println()      { print(); }

        template <typename T1, typename T2, typename T3>
        void print(T1 n1, T2 n2, T3 n3);
        
        template <typename T1, typename T2, typename T3>
        void println(T1 n1, T2 n2, T3 n3)   { print(n1, n2, n3); }

        template <typename T1>
        void printArray(T1 n1, const String &s2);

        template <typename T1>
        void printObject(T1 n1, const String &s2);

        template <typename T1>
        void print(T1 n1, const String &s2);
        template <typename T1>
        void print(T1 n1, const char str2[]);
        template <typename T1>
        void print(T1 n1, char c);
        template <typename T1>
        void print(T1 n1, unsigned char b);
        template <typename T1>
        void print(T1 n1, int n);
        template <typename T1>
        void print(T1 n1, unsigned int n);
        template <typename T1>
        void print(T1 n1, long n);
        template <typename T1>
        void print(T1 n1, unsigned long n);
        template <typename T1>
        void print(T1 n1, double n);

        template <typename T1>
        void println(T1 n1, const String &s2)   { print(n1, s2); }
        template <typename T1>
        void println(T1 n1, const char str2[])  { print(n1, str2); }
        template <typename T1>
        void println(T1 n1, char c)             { print(n1, c); }
        template <typename T1>
        void println(T1 n1, unsigned char b)    { print(n1, b); }
        template <typename T1>
        void println(T1 n1, int n)              { print(n1, n); }
        template <typename T1>
        void println(T1 n1, unsigned int n)     { print(n1, n); }        
        template <typename T1>
        void println(T1 n1, long n)             { print(n1, n); }        
        template <typename T1>
        void println(T1 n1, unsigned long n)    { print(n1, n); }        
        template <typename T1>
        void println(T1 n1, double n)           { print(n1, n); }

        template <typename T>
        void notify(T n);
        void vibrate(uint16_t ms = 200);
        void delay(unsigned long ms);
        void attachAhrs();
        void detachAhrs();
        int16_t ahrs(b_ahrsattitude_t attitude) { return ahrsValue[attitude]; }
        float gps(b_gps_t axis);

        #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
            defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            void setTimezone(float tz);
            float getTimezone() { return _timezone; }
            int8_t second();
            int8_t minute();
            int8_t hour();
            int8_t mday();
            int8_t wday();
            int8_t month();
            int16_t year();
            int16_t yday();
            time_t  time();
            int32_t dtime();

            template<typename T>
            bool sms(const T& msg);
            template<typename T>
            bool sms(const T& msg, const char* cel);
            template<typename T>
            bool push(const T& msg);
            template<typename T>
            bool wechat(const T& msg);
            template<typename T>
            bool wechat(const String & title, const String & state, const T& msg);
            String weather(const String & _city = BLINKER_CMD_DEFAULT);
            String aqi(const String & _city = BLINKER_CMD_DEFAULT);
            
            void loadTimer();
            void deleteTimer();
            void deleteCountdown();
            void deleteLoop();
            void deleteTiming();
            bool countdownState()   { return _cdState; }
            bool loopState()        { return _lpState; }
            bool timingState()      { return taskCount ? true : false; }

            template<typename T>
            bool configUpdate(const T& msg);
            String configGet();
            bool configDelete();
            template<typename T>
            void dataStorage(char _name[], const T& msg);
            bool dataUpdate();
            String dataGet();
            String dataGet(const String & _type);
            String dataGet(const String & _type, const String & _date);
            bool dataDelete();
            bool dataDelete(const String & _type);
            
            // bool bridge(char _name[]);
            bool autoPull();
            void autoInit()         { autoStart(); }
            void autoInput(const String & key, const String & state);
            void autoInput(const String & key, float data);
            void autoRun();

            void freshAttachBridge(char _key[], blinker_callback_with_string_arg_t _func);
            uint8_t attachBridge(char _key[], blinker_callback_with_string_arg_t _func);
            char * bridgeKey(uint8_t num);
            char * bridgeName(uint8_t num);
            void bridgeInit();

            void bridgePrint(char * bName, const String & data);
            void aligeniePrint(String & _msg);
            void duerPrint(String & _msg);

            void loadOTA();
            void ota();
            String checkOTA();
            bool updateOTAStatus(int8_t status, const String & msg);
            void otaStatus(int8_t status, const String & msg);

        #endif

        #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
            defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT) || \
            defined(BLINKER_MQTT_AT)

            #if defined(BLINKER_ALIGENIE)
                void attachAliGenieSetPowerState(blinker_callback_with_string_arg_t newFunction)
                { _AliGeniePowerStateFunc = newFunction; }
                void attachAliGenieSetColor(blinker_callback_with_string_arg_t newFunction)
                { _AliGenieSetColorFunc = newFunction; }
                void attachAliGenieSetMode(blinker_callback_with_string_arg_t newFunction)
                { _AliGenieSetModeFunc = newFunction; }
                void attachAliGenieSetcMode(blinker_callback_with_string_arg_t newFunction)
                { _AliGenieSetcModeFunc = newFunction; }
                void attachAliGenieSetBrightness(blinker_callback_with_string_arg_t newFunction)
                { _AliGenieSetBrightnessFunc = newFunction; }
                void attachAliGenieRelativeBrightness(blinker_callback_with_int32_arg_t newFunction)
                { _AliGenieSetRelativeBrightnessFunc = newFunction; }
                void attachAliGenieSetColorTemperature(blinker_callback_with_int32_arg_t newFunction)
                { _AliGenieSetColorTemperature = newFunction; }
                void attachAliGenieRelativeColorTemperature(blinker_callback_with_int32_arg_t newFunction)
                { _AliGenieSetRelativeColorTemperature = newFunction; }
                void attachAliGenieQuery(blinker_callback_with_int32_arg_t newFunction)
                { _AliGenieQueryFunc = newFunction; }
            #endif

            #if defined(BLINKER_DUEROS)
                void attachDuerOSSetPowerState(blinker_callback_with_string_arg_t newFunction)
                { _DuerOSPowerStateFunc = newFunction; }
                void attachDuerOSSetColor(blinker_callback_with_int32_arg_t newFunction)
                { _DuerOSSetColorFunc = newFunction; }
                void attachDuerOSSetMode(blinker_callback_with_string_arg_t newFunction)
                { _DuerOSSetModeFunc = newFunction; }
                void attachDuerOSSetcMode(blinker_callback_with_string_arg_t newFunction)
                { _DuerOSSetcModeFunc = newFunction; }
                void attachDuerOSSetBrightness(blinker_callback_with_string_arg_t newFunction)
                { _DuerOSSetBrightnessFunc = newFunction; }
                void attachDuerOSRelativeBrightness(blinker_callback_with_int32_arg_t newFunction)
                { _DuerOSSetRelativeBrightnessFunc = newFunction; }
                // void attachDuerOSSetColorTemperature(blinker_callback_with_int32_arg_t newFunction)
                // { _DuerOSSetColorTemperature = newFunction; }
                // void attachDuerOSRelativeColorTemperature(blinker_callback_with_int32_arg_t newFunction)
                // { _DuerOSSetRelativeColorTemperature = newFunction; }
                void attachDuerOSQuery(blinker_callback_with_int32_arg_t newFunction)
                { _DuerOSQueryFunc = newFunction; }
            #endif
        #endif

        // #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_MQTT_AT)
        //     void bridgePrint(char * bName, const String & data);
        //     void aligeniePrint(String & _msg);
        //     void duerPrint(String & _msg);
        // #endif

        #if defined(BLINKER_MQTT_AT)
            // class BlinkerMasterAT *         _masterAT;
            // void atRespOK(const String & _data, uint32_t timeout = BLINKER_STREAM_TIMEOUT*10);
            void initCheck(const String & _data, uint32_t timeout = BLINKER_STREAM_TIMEOUT*10);
            void atResp();
            void parseATdata();
            int analogRead();
            void pinMode(uint8_t pin, uint8_t mode);
            void digitalWrite(uint8_t pin, uint8_t val);
            int digitalRead(uint8_t pin);
            void setTimezone(float tz);
            float getTimezone();
            int32_t atGetInt(const String & cmd);
            template<typename T>
            String atGetString(const String & cmd, const T& msg);
            time_t time()   { return atGetInt(BLINKER_CMD_TIME_AT); }
            // time_t dtime()   { return atGetInt(BLINKER_CMD_D); }
            int8_t second() { return atGetInt(BLINKER_CMD_SECOND); }
            int8_t minute() { return atGetInt(BLINKER_CMD_MINUTE); }
            int8_t hour()   { return atGetInt(BLINKER_CMD_HOUR); }
            int8_t mday()   { return atGetInt(BLINKER_CMD_MDAY); }
            int8_t wday()   { return atGetInt(BLINKER_CMD_WDAY); }
            int8_t month()  { return atGetInt(BLINKER_CMD_MONTH); }
            int16_t year()  { return atGetInt(BLINKER_CMD_YEAR); }
            int16_t yday()  { return atGetInt(BLINKER_CMD_YDAY); }
            String weather(const String & _city = BLINKER_CMD_DEFAULT);
            String aqi(const String & _city = BLINKER_CMD_DEFAULT);
            template<typename T>
            bool sms(const T& msg);
            void reset();
        #endif
        
        void attachData(blinker_callback_with_string_arg_t newFunction)
        { _availableFunc = newFunction; }
        void attachHeartbeat(blinker_callback_t newFunction)
        { _heartbeatFunc = newFunction; }
        void attachSummary(blinker_callback_return_string_t newFunction)
        { _summaryFunc = newFunction; }

        void freshAttachWidget(char _name[], blinker_callback_with_string_arg_t _func);
        #if defined(BLINKER_BLE)
            void freshAttachWidget(char _name[], blinker_callback_with_joy_arg_t _func);
        #endif
        void freshAttachWidget(char _name[], blinker_callback_with_rgb_arg_t _func);
        void freshAttachWidget(char _name[], blinker_callback_with_int32_arg_t _func);
        uint8_t attachWidget(char _name[], blinker_callback_with_string_arg_t _func);
        #if defined(BLINKER_BLE)
            uint8_t attachWidget(char _name[], blinker_callback_with_joy_arg_t _func);
        #endif
        uint8_t attachWidget(char _name[], blinker_callback_with_rgb_arg_t _func);
        uint8_t attachWidget(char _name[], blinker_callback_with_int32_arg_t _func);
        void attachSwitch(blinker_callback_with_string_arg_t _func);
        char * widgetName_str(uint8_t num);
        #if defined(BLINKER_BLE)
            char * widgetName_joy(uint8_t num);
        #endif
        char * widgetName_rgb(uint8_t num);
        char * widgetName_int(uint8_t num);

        #if defined(BLINKER_PRO)
            void attachParse(blinker_callback_with_json_arg_t newFunction)
            { _parseFunc = newFunction; }
            void attachClick(blinker_callback_t newFunction)
            { _clickFunc = newFunction; }
            void attachDoubleClick(blinker_callback_t newFunction)
            { _doubleClickFunc = newFunction; }
            void attachLongPressStart(blinker_callback_t newFunction)
            { _longPressStartFunc = newFunction; }
            void attachLongPressStop(blinker_callback_t newFunction)
            { _longPressStopFunc = newFunction; }
            void attachDuringLongPress(blinker_callback_t newFunction)
            { _duringLongPressFunc = newFunction; }
            #if defined(BLINKER_BUTTON_LONGPRESS_POWERDOWN)
                void attachLongPressPowerdown(blinker_callback_t newFunction)
                { _powerdownFunc = newFunction; }
                void attachLongPressReset(blinker_callback_t newFunction)
                { _resetFunc = newFunction; }

                uint16_t pressedTime();
            #endif

            void setType(const char* _type);
            const char* type() { return _deviceType; }
            void reset();
            void tick();
            void checkRegister(const JsonObject& data);            
            
            bool init()                         { return _isInit; }
            bool registered()                   { return BProto::authCheck(); }
            uint8_t status()                    { return _proStatus; }
        #endif

    private :
        bool        _fresh = false;
        int16_t     ahrsValue[3];
        float       gpsValue[2];
        uint32_t    gps_get_time;
        
        uint8_t     _wCount_str = 0;
        uint8_t     _wCount_joy = 0;
        uint8_t     _wCount_rgb = 0;
        uint8_t     _wCount_int = 0;

        class BlinkerWidgets_string *       _Widgets_str[BLINKER_MAX_WIDGET_SIZE*2];
        #if defined(BLINKER_BLE)
            class BlinkerWidgets_joy *          _Widgets_joy[BLINKER_MAX_WIDGET_SIZE/2];
        #endif
        class BlinkerWidgets_rgb *          _Widgets_rgb[BLINKER_MAX_WIDGET_SIZE/2];
        class BlinkerWidgets_int32 *        _Widgets_int[BLINKER_MAX_WIDGET_SIZE*2];
        // class BlinkerWidgets_string *       _BUILTIN_SWITCH;
        BlinkerWidgets_string _BUILTIN_SWITCH = BlinkerWidgets_string(BLINKER_CMD_BUILTIN_SWITCH);

        #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
            defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            bool        _isInit = false;
            bool        _isAuto = false;
            bool        _isAutoInit = false;
            uint8_t     _disconnectCount = 0;
            uint32_t    _disFreshTime = 0;
            uint32_t    _disconnectTime = 0;
            uint32_t    _refreshTime = 0;
            uint32_t    _reconTime = 0;

            bool        _isNTPInit = false;
            float       _timezone = 8.0;
            uint32_t    _ntpStart;

            uint32_t    _smsTime = 0;
            uint32_t    _pushTime = 0;
            uint32_t    _wechatTime = 0;
            uint32_t    _weatherTime = 0;
            uint32_t    _aqiTime = 0;
            uint8_t     data_dataCount = 0;
            uint8_t     _aCount = 0;
            uint8_t     _bridgeCount = 0;

            uint32_t    _cUpdateTime = 0;
            uint32_t    _dUpdateTime = 0;
            uint32_t    _cGetTime = 0;
            uint32_t    _cDelTime = 0;
            uint32_t    _dGetTime = 0;
            uint32_t    _dDelTime = 0;
            uint32_t    _autoPullTime = 0;

            char                            _cdAction[BLINKER_TIMER_COUNTDOWN_ACTION_SIZE];
            char                            _lpAction1[BLINKER_TIMER_LOOP_ACTION1_SIZE];
            char                            _lpAction2[BLINKER_TIMER_LOOP_ACTION2_SIZE];
            class BlinkerTimingTimer *      timingTask[BLINKER_TIMING_TIMER_SIZE];
            class BlinkerBridge_key *       _Bridge[BLINKER_MAX_BRIDGE_SIZE];
            class BlinkerData *             _Data[BLINKER_MAX_BLINKER_DATA_SIZE];
            class BlinkerAUTO *             _AUTO[2];
            BlinkerOTA                      _OTA;
        #endif

        #if defined(BLINKER_PRO)
            bool            _isConnBegin = false;
            bool            _getRegister = false;
            // bool            _isInit = false;
            bool            _isRegistered = false;
            uint32_t        _register_fresh = 0;
            uint32_t        _initTime;
            uint8_t         _proStatus = PRO_WLAN_CONNECTING;
        #endif

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_MQTT_AT)
            blinker_callback_with_string_arg_t  _AliGeniePowerStateFunc = NULL;
            blinker_callback_with_string_arg_t  _AliGenieSetColorFunc = NULL;
            blinker_callback_with_string_arg_t  _AliGenieSetModeFunc = NULL;
            blinker_callback_with_string_arg_t  _AliGenieSetcModeFunc = NULL;
            blinker_callback_with_string_arg_t  _AliGenieSetBrightnessFunc = NULL;
            blinker_callback_with_int32_arg_t   _AliGenieSetRelativeBrightnessFunc = NULL;
            blinker_callback_with_int32_arg_t   _AliGenieSetColorTemperature = NULL;
            blinker_callback_with_int32_arg_t   _AliGenieSetRelativeColorTemperature = NULL;
            blinker_callback_with_int32_arg_t   _AliGenieQueryFunc = NULL;

            blinker_callback_with_string_arg_t  _DuerOSPowerStateFunc = NULL;
            blinker_callback_with_int32_arg_t   _DuerOSSetColorFunc = NULL;
            blinker_callback_with_string_arg_t  _DuerOSSetModeFunc = NULL;
            blinker_callback_with_string_arg_t  _DuerOSSetcModeFunc = NULL;
            blinker_callback_with_string_arg_t  _DuerOSSetBrightnessFunc = NULL;
            blinker_callback_with_int32_arg_t   _DuerOSSetRelativeBrightnessFunc = NULL;
            // blinker_callback_with_int32_arg_t   _DuerOSSetColorTemperature = NULL;
            // blinker_callback_with_int32_arg_t   _DuerOSSetRelativeColorTemperature = NULL;
            blinker_callback_with_int32_arg_t   _DuerOSQueryFunc = NULL;
        #endif

        #if defined(BLINKER_MQTT_AT)
            class BlinkerMasterAT *         _masterAT;
            void atRespOK(const String & _data, uint32_t timeout = BLINKER_STREAM_TIMEOUT*10);
            // void initCheck(const String & _data, uint32_t timeout = BLINKER_STREAM_TIMEOUT*10);
        #endif

        blinker_callback_t                  _heartbeatFunc = NULL;
        blinker_callback_return_string_t    _summaryFunc = NULL;
        
        void parse(char _data[], bool ex_data = false);

        #if defined(BLINKER_ARDUINOJSON)
            int16_t ahrs(b_ahrsattitude_t attitude, const JsonObject& data);
            float gps(b_gps_t axis, const JsonObject& data);

            void heartBeat(const JsonObject& data);
            void getVersion(const JsonObject& data);
            void setSwitch(const JsonObject& data);

            #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                void bridgeParse(char _bName[], const JsonObject& data);
            #endif
            void strWidgetsParse(char _wName[], const JsonObject& data);
            #if defined(BLINKER_BLE)
                void joyWidgetsParse(char _wName[], const JsonObject& data);
            #endif
            void rgbWidgetsParse(char _wName[], const JsonObject& data);
            void intWidgetsParse(char _wName[], const JsonObject& data);

            void json_parse(const JsonObject& data);
        #else
            int16_t ahrs(b_ahrsattitude_t attitude, char data[]);
            float gps(b_gps_t axis, char data[]);

            void heartBeat(char data[]);
            void getVersion(char data[]);
            void setSwitch(char data[]);

            void strWidgetsParse(char _wName[], char _data[]);
            #if defined(BLINKER_BLE)
                void joyWidgetsParse(char _wName[], char _data[]);
            #endif
            void rgbWidgetsParse(char _wName[], char _data[]);
            void intWidgetsParse(char _wName[], char _data[]);

            void json_parse(char _data[]);
        #endif

        #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
            defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            void beginAuto();
            bool autoTrigged(uint32_t _id);
            bool checkCanOTA();

            void freshNTP();
            bool ntpInit();
            void ntpConfig();

            void saveCountDown(uint32_t _data, char _action[]);
            void saveLoop(uint32_t _data, char _action1[], char _action2[]);
            void loadCountdown();
            void loadLoop();
            void loadTiming();
            void checkOverlapping(uint8_t checkDays, uint16_t checkMins);
            void freshTiming(uint8_t wDay, uint16_t nowMins);
            void deleteTiming(uint8_t taskDel);
            void addTimingTask(uint8_t taskSet, uint32_t timerData, const String & action);
            
            // #if defined(ESP32)
            //     uint8_t isErase;
            // #endif
            
            void checkTimerErase();
            
            String timerSetting();
            String countdownConfig();
            String loopConfig();
            String timingConfig();
            String getTimingCfg(uint8_t task);
            bool timerManager(const JsonObject& data, bool _noSet = false);
            bool checkTimer();
            bool checkSMS();
            bool checkPUSH();
            bool checkWECHAT();
            bool checkWEATHER();
            bool checkAQI();

            void autoStart();
            bool autoManager(const JsonObject& data);
            void otaPrase(const JsonObject& data);
            
            bool checkCUPDATE();
            bool checkCGET();
            bool checkCDEL();
            bool checkDataUpdata();
            bool checkDataGet();
            bool checkDataDel();
            bool checkAutoPull();
            String bridgeQuery(char * key);

            String postServer(const String & url, const String & host, int port, const String & msg);
            String getServer(const String & url, const String & host, int port);
            String blinkerServer(uint8_t _type, const String & msg, bool state = false);
        #endif

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_MQTT_AT)
            void aliParse(const String & _data);
            void duerParse(const String & _data);
        #endif

        #if defined(BLINKER_AT_MQTT)
            blinker_at_status_t     _status = BL_BEGIN;
            blinker_at_aligenie_t   _aliType = ALI_NONE;
            blinker_at_dueros_t     _duerType = DUER_NONE;
            uint8_t                 _wlanMode = BLINKER_CMD_COMCONFIG_NUM;
            uint8_t                 pinDataNum = 0;
            class BlinkerSlaverAT * _slaverAT;
            class PinData *         _pinData[BLINKER_MAX_PIN_NUM];
            
            void parseATdata();
            String getMode(uint8_t mode);
            bool serialAvailable();
            void serialPrint(const String & s);
            void atHeartbeat();
        #endif

    protected :
        void begin();

        #if defined(BLINKER_AT_MQTT)
            void atBegin();
        #endif

        #if defined(BLINKER_MQTT_AT)
            void atInit(const char* _auth);
            void atInit(const char* _auth, const char* _ssid, const char* _pswd);
        #endif

        #if defined(BLINKER_PRO)
            bool beginPro() { return wlanRun(); }
            void begin(const char* _type);

            const char* _deviceType;
            BlinkerWlan Bwlan;

            blinker_callback_with_json_arg_t    _parseFunc = NULL;

            #if defined(BLINKER_BUTTON_LONGPRESS_POWERDOWN)
                blinker_callback_t _powerdownFunc = NULL;
                blinker_callback_t _resetFunc = NULL;
            #endif
            // OneButton   button1;

            int _pin;        // hardware pin number.
            int _debounceTicks; // number of ticks for debounce times.
            int _clickTicks; // number of ticks that have to pass by before a click is detected
            int _pressTicks; // number of ticks that have to pass by before a long button press is detected

            int _buttonReleased;
            int _buttonPressed;

            bool _isLongPressed;

            // These variables will hold functions acting as event source.
            blinker_callback_t _clickFunc;
            blinker_callback_t _doubleClickFunc;
            blinker_callback_t _pressFunc;
            blinker_callback_t _longPressStartFunc;
            blinker_callback_t _longPressStopFunc;
            blinker_callback_t _duringLongPressFunc;

            // These variables that hold information across the upcoming tick calls.
            // They are initialized once on program start and are updated every time the tick function is called.
            int _state;
            unsigned long _startTime; // will be set in state 1
            unsigned long _stopTime; // will be set in state 2

            bool wlanRun()
            {
                #if defined(BLINKER_BUTTON)
                    tick();
                #endif
                return Bwlan.run();
            }

            uint8_t wlanStatus() { return Bwlan.status(); }

            bool isPressed = false;

            void _click() { BLINKER_LOG_ALL(BLINKER_F("Button click.")); } // click

            void _doubleClick() { BLINKER_LOG_ALL(BLINKER_F("Button doubleclick.")); } // doubleclick1

            void _longPressStart()
            {
                BLINKER_LOG_ALL(BLINKER_F("Button longPress start"));
                // _longPressStartFunc();
                isPressed = true;
            } // longPressStart

            void _longPress()
            {
                if (isPressed)
                {
                    BLINKER_LOG_ALL(BLINKER_F("Button longPress..."));                    
                    isPressed = false;
                }// _duringLongPressFunc();
            } // longPress

            void _longPressStop()
            {
                BLINKER_LOG_ALL(BLINKER_F("Button longPress stop"));
                // _longPressStopFunc();
                // Bwlan.deleteConfig();
                // Bwlan.reset();
                // ESP.restart();
                // reset();

                uint32_t _pressedTime = millis() - _startTime;
                
                BLINKER_LOG_ALL(BLINKER_F("_stopTime: "), millis(), BLINKER_F(" ,_startTime: "), _startTime);
                BLINKER_LOG_ALL(BLINKER_F("long pressed time: "), _pressedTime);

                #if defined(BLINKER_BUTTON_LONGPRESS_POWERDOWN)
                    if (_pressedTime >= BLINKER_PRESSTIME_RESET) {
                        if (_resetFunc) {
                            _resetFunc();
                        }

                        reset();
                    }
                    else {
                        BLINKER_LOG(BLINKER_F("BLINKER_PRESSTIME_POWERDOWN"));

                        if (_powerdownFunc) {
                            _powerdownFunc();
                        }
                    }
                #else
                    // if (_resetFunc) {
                    //     _resetFunc();
                    // }

                    reset();
                #endif
            } // longPressStop

            void buttonInit(int activeLow = true)
            {
                _pin = BLINKER_BUTTON_PIN;

                _debounceTicks = 50;      // number of millisec that have to pass by before a click is assumed as safe.
                _clickTicks = 600;        // number of millisec that have to pass by before a click is detected.
                _pressTicks = 1000;       // number of millisec that have to pass by before a long button press is detected.

                _state = 0; // starting with state 0: waiting for button to be pressed
                _isLongPressed = false;  // Keep track of long press state

                if (activeLow) {
                    // the button connects the input pin to GND when pressed.
                    _buttonReleased = HIGH; // notPressed
                    _buttonPressed = LOW;

                    // use the given pin as input and activate internal PULLUP resistor.
                    pinMode( _pin, INPUT_PULLUP );

                } else {
                    // the button connects the input pin to VCC when pressed.
                    _buttonReleased = LOW;
                    _buttonPressed = HIGH;

                    // use the given pin as input
                    pinMode(_pin, INPUT);
                } // if

                _clickFunc = NULL;
                _doubleClickFunc = NULL;
                _pressFunc = NULL;
                _longPressStartFunc = NULL;
                _longPressStopFunc = NULL;
                _duringLongPressFunc = NULL;

                // attachInterrupt(BLINKER_BUTTON_PIN, checkButton, CHANGE);

                BLINKER_LOG_ALL(BLINKER_F("Button initialled"));
            }

        #endif
};

void BlinkerApi::begin()
{
    BLINKER_LOG(BLINKER_F(""));
    #if defined(BLINKER_NO_LOGO)
        BLINKER_LOG(BLINKER_F("Blinker v"), BLINKER_VERSION, BLINKER_F("\n"),
                    BLINKER_F("    Give Blinker a Github star, thanks!\n"),
                    BLINKER_F("    => https://github.com/blinker-iot/blinker-library\n"));
    #elif defined(BLINKER_LOGO_3D)
        BLINKER_LOG(BLINKER_F("\n"),
                    BLINKER_F(" ____    ___                __                       \n"),
                    BLINKER_F("/\\  _`\\ /\\_ \\    __        /\\ \\               v"), BLINKER_VERSION, BLINKER_F("\n"),
                    BLINKER_F("\\ \\ \\L\\ \\//\\ \\  /\\_\\    ___\\ \\ \\/'\\      __   _ __   \n"),
                    BLINKER_F(" \\ \\  _ <'\\ \\ \\ \\/\\ \\ /' _ `\\ \\ , <    /'__`\\/\\`'__\\ \n"),
                    BLINKER_F("  \\ \\ \\L\\ \\\\_\\ \\_\\ \\ \\/\\ \\/\\ \\ \\ \\\\`\\ /\\  __/\\ \\ \\/  \n"),
                    BLINKER_F("   \\ \\____//\\____\\\\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\ \\____\\\\ \\_\\  \n"),
                    BLINKER_F("    \\/___/ \\/____/ \\/_/\\/_/\\/_/\\/_/\\/_/\\/____/ \\/_/  \n"),
                    BLINKER_F("   Give Blinker a Github star, thanks!\n"),
                    BLINKER_F("   => https://github.com/blinker-iot/blinker-library\n"));
    #else
        BLINKER_LOG(BLINKER_F("\n"),
                    BLINKER_F("   ___  ___      __    v"), BLINKER_VERSION, BLINKER_F("\n"),
                    BLINKER_F("  / _ )/ (_)__  / /_____ ____\n"),
                    BLINKER_F(" / _  / / / _ \\/  '_/ -_) __/\n")
                    BLINKER_F("/____/_/_/_//_/_/\\_\\\\__/_/   \n")
                    BLINKER_F("Give Blinker a github star, thanks!\n")
                    BLINKER_F("=> https://github.com/blinker-iot/blinker-library\n"));
    #endif

    #if defined(BLINKER_OTA_VERSION_CODE) && (defined(BLINKER_MQTT) || defined(BLINKER_MQTT_AT))
        if (strlen(BLINKER_OTA_VERSION_CODE) >= BLINKER_OTA_INFO_SIZE)
        {
            while(1)
            {
                BLINKER_ERR_LOG(BLINKER_F("The OTA version code you set is too long!"));
                ::delay(10000);
            }
        }
    #endif
}

#if defined(BLINKER_PRO)
    void BlinkerApi::begin(const char* _type)
    {
        begin();

        BLINKER_LOG(BLINKER_F(
                    "\n==========================================================="
                    "\n================= Blinker PRO mode init ! ================="
                    "\nWarning! EEPROM address 1280-1535 is used for Auto Control!"
                    "\n============= DON'T USE THESE EEPROM ADDRESS! ============="
                    "\n===========================================================\n"));

        BLINKER_LOG(BLINKER_F("Already used: "), BLINKER_ONE_AUTO_DATA_SIZE);

        #if defined(BLINKER_BUTTON)
            #if defined(BLINKER_BUTTON_PULLDOWN)
                buttonInit(false);
            #else
                buttonInit();
            #endif
        #endif

        setType(_type);
    }
#endif

void BlinkerApi::run()
{
    #if defined(BLINKER_PRO)

        if (!wlanRun())
        {
            uint8_t wl_status = wlanStatus();
            
            if (wl_status == BWL_SMARTCONFIG_BEGIN) {
                _proStatus = PRO_WLAN_SMARTCONFIG_BEGIN;
            }
            else if (wl_status == BWL_SMARTCONFIG_DONE) {
                _proStatus = PRO_WLAN_SMARTCONFIG_DONE;
            }
            else {
                _proStatus = PRO_WLAN_CONNECTING;
            }
            return;
        }
        else
        {
            if (!_isConnBegin)
            {
                _proStatus = PRO_WLAN_CONNECTED;

                if (checkCanOTA()) loadOTA();

                BProto::begin(type());
                _isConnBegin = true;
                _initTime = millis();
                
                BLINKER_LOG_ALL(BLINKER_F("conn begin, fresh _initTime: "), _initTime);

                // loadOTA();

                if (BProto::authCheck())
                {
                    _proStatus = PRO_DEV_AUTHCHECK_SUCCESS;

                    BLINKER_LOG_ALL(BLINKER_F("is auth, conn deviceRegister"));

                    _isRegistered = BProto::deviceRegister();
                    _getRegister = true;

                    if (!_isRegistered)
                    {
                        _register_fresh = millis();

                        _proStatus = PRO_DEV_REGISTER_FAIL;
                    }
                    else
                    {
                        _proStatus = PRO_DEV_REGISTER_SUCCESS;
                    }
                }
                else
                {
                    _proStatus = PRO_DEV_AUTHCHECK_FAIL;

                    BLINKER_LOG_ALL(BLINKER_F("not auth, conn deviceRegister"));
                }

                BLINKER_LOG_FreeHeap_ALL();
            }
        }

        if (_getRegister)
        {
            if (!_isRegistered && ((millis() - _register_fresh) > 5000 || \
                _register_fresh == 0))
            {
                BLINKER_LOG_ALL(BLINKER_F("conn deviceRegister"));
                
                _isRegistered = BProto::deviceRegister();

                if (!_isRegistered)
                {
                    _register_fresh = millis();
                    _proStatus = PRO_DEV_REGISTER_FAIL;
                }
                else
                {
                    _isRegistered = true;
                    _proStatus = PRO_DEV_REGISTER_SUCCESS;
                }
            }
        }
        
        if (!BProto::init())
        {
            yield();

            if ((millis() - _initTime) >= BLINKER_CHECK_AUTH_TIME && \
                !_getRegister)
            {
                reset();
            }
        }
        else
        {
            if (!_isInit)
            {
                if (ntpInit())
                {
                    _isInit = true;
                    // strcpy(_authKey, conn.authKey());
                    // strcpy(_deviceName, conn.deviceName());
                    _proStatus = PRO_DEV_INIT_SUCCESS;

                    uint32_t connect_time = millis();
                    uint32_t time_slot = 0;

                    while (time_slot < 30000)
                    {
                        time_slot = millis() - connect_time;
                        BProto::connect();
                        yield();

                        if (BProto::mConnected())
                        {
                            state = CONNECTED;
                            break;
                        }
                    }

                    // if (checkCanOTA()) loadOTA();
                }
            }
            else
            {
                if (state == CONNECTING && _proStatus != PRO_DEV_CONNECTING) {
                    _proStatus = PRO_DEV_CONNECTING;
                }
                else if (state == CONNECTED && _proStatus != PRO_DEV_CONNECTED) {
                    if (BProto::mConnected()) _proStatus = PRO_DEV_CONNECTED;
                }
                else if (state == DISCONNECTED && _proStatus != PRO_DEV_DISCONNECTED) {
                    _proStatus = PRO_DEV_DISCONNECTED;
                }
            }
        }

    #endif

    #if defined(BLINKER_PRO)
        ntpInit();
        checkTimer();
    #endif

    #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || defined(BLINKER_AT_MQTT)
        checkTimer();

        if (!_isInit)
        {
            if (BProto::init() && ntpInit())
            {
                _isInit =true;
                _disconnectTime = millis();

                uint32_t connect_time = millis();
                uint32_t time_slot = 0;

                while (time_slot < 30000)
                {
                    time_slot = millis() - connect_time;
                    BProto::connect();
                    yield();

                    if (BProto::mConnected())
                    {
                        state = CONNECTED;
                        break;
                    }
                }

                BLINKER_LOG_ALL(BLINKER_F("millis: "), millis(),
                                BLINKER_F(", connect_time: "), connect_time);

                if (checkCanOTA()) loadOTA();

                bridgeInit();
                
                BLINKER_LOG_ALL(BLINKER_F("MQTT conn init success"));
            }
        }
        else {
            ntpInit();
        }
    #endif

    #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || defined(BLINKER_AT_MQTT)
        if (WiFi.status() != WL_CONNECTED)
        {        
            if ((millis() - _reconTime) >= 10000 || \
                _reconTime == 0 )
            {
                _reconTime = millis();
                BLINKER_LOG(BLINKER_F("WiFi disconnected! reconnecting!"));
                WiFi.reconnect();
            }

            return;
        }
    #endif

    bool conState = BProto::connected();

    switch (BProto::state)
    {
        case CONNECTING :
            if (BProto::connect())
            {
                BProto::state = CONNECTED;

                #if defined(BLINKER_MQTT) || defined(BLINKER_AT_MQTT)
                    _disconnectCount = 0;
                #endif
            }
            else
            {
                #if defined(BLINKER_MQTT) || defined(BLINKER_AT_MQTT)
                    if (_isInit)
                    {
                        if (_disconnectCount == 0)
                        {
                            _disconnectCount++;
                            _disconnectTime = millis();
                            _disFreshTime = millis();
                        }
                        else
                        {
                            // if ((millis() > _disFreshTime) && (millis() - _disFreshTime) >= 5000) {
                            if ((millis() - _disFreshTime) >= BLINKER_MQTT_CONNECT_TIMESLOT)
                            {
                                _disFreshTime = millis();
                                _disconnectCount++;

                                if (_disconnectCount > 12) _disconnectCount = 12;

                                BLINKER_LOG_ALL(BLINKER_F("_disFreshTime: "), _disFreshTime);
                                BLINKER_LOG_ALL(BLINKER_F("_disconnectCount: "), _disconnectCount);
                            }
                        }
                    }
                #endif
            }
            break;
        case CONNECTED :
            if (conState)
            {
                BProto::checkAvail();
                if (BProto::isAvail)
                {
                    parse(BProto::dataParse());
                }

                #if (defined(BLINKER_MQTT) || defined(BLINKER_PRO)) 
                    #if defined(BLINKER_ALIGENIE)
                        if (BProto::checkAliAvail())
                        {
                            aliParse(BProto::lastRead());
                        }
                    #endif

                    #if defined(BLINKER_DUEROS)
                        if (BProto::checkDuerAvail())
                        {
                            duerParse(BProto::lastRead());
                        }
                    #endif
                #endif

                #if defined(BLINKER_MQTT_AT) && defined(BLINKER_ALIGENIE)
                    if (isAvail)
                    {
                        aliParse(BProto::lastRead());

                        if (STRING_contains_string(BProto::lastRead(), "AliGenie"))
                        {
                            flush();
                        }
                    }
                #endif

                #if defined(BLINKER_AT_MQTT)
                    if (isAvail)
                    {
                        // BLINKER_LOG_ALL("isAvail");
                        BProto::serialPrint(BProto::lastRead());
                    }

                    if (serialAvailable())
                    {
                        BProto::mqttPrint(BProto::serialLastRead());
                    }
                #endif

                if (BProto::availState)
                {
                    BProto::availState = false;

                    if (BProto::_availableFunc)
                    {
                        BProto::_availableFunc(BProto::lastRead());
                        flush();
                    }
                }
            }
            else
            {
                BProto::disconnect();
                BProto::state = CONNECTING;

                #if defined(BLINKER_MQTT) || defined(BLINKER_AT_MQTT)
                    if (_isInit)
                    {
                        if (_disconnectCount == 0)
                        {
                            _disconnectCount++;
                            _disconnectTime = millis();
                            _disFreshTime = millis();
                        }
                        else
                        {
                            if ((millis() - _disFreshTime) >= 5000)
                            {
                                _disFreshTime = millis();
                                _disconnectCount++;

                                if (_disconnectCount > 12) _disconnectCount = 12;
                                
                                BLINKER_LOG_ALL(BLINKER_F("_disFreshTime: "), _disFreshTime);
                                BLINKER_LOG_ALL(BLINKER_F("_disconnectCount: "), _disconnectCount);
                            }
                        }
                    }
                #endif
            }
            break;
        case DISCONNECTED :
            BProto::disconnect();
            BProto::state = CONNECTING;
            break;
    }

    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        if (_isAuto && _isInit && state == CONNECTED && !_isAutoInit)
        {
            if (autoPull()) _isAutoInit = true;
        }
    #endif

    BProto::checkAutoFormat();
}

void BlinkerApi::parse(char _data[], bool ex_data)
{
    BLINKER_LOG_ALL(BLINKER_F("parse data: "), _data);
    
    if (!ex_data)
    {
        if (BProto::parseState())
        {
            _fresh = false;

            #if defined(BLINKER_ARDUINOJSON)
                BLINKER_LOG_ALL(BLINKER_F("defined BLINKER_ARDUINOJSON"));

                DynamicJsonBuffer jsonBuffer;
                JsonObject& root = jsonBuffer.parseObject(STRING_format(_data));

                if (!root.success()) 
                {
                    #if defined(BLINKER_MQTT_AT)
                        atResp();
                    #endif
                    return;
                }

                #if defined(BLINKER_PRO)
                    checkRegister(root);
                #endif

                // #if defined(BLINKER_MQTT) || defined(BLINKER_PRO)

                #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
                    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                    timerManager(root);
                    // BLINKER_LOG_ALL(BLINKER_F("timerManager"));
                #endif

                #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                    autoManager(root);
                    otaPrase(root);

                    for (uint8_t bNum = 0; bNum < _bridgeCount; bNum++)
                    {
                        bridgeParse(_Bridge[bNum]->getName(), root);
                    }
                #endif

                heartBeat(root);
                getVersion(root);

                json_parse(root);

                ahrs(Yaw, root);
                gps(LONG, root);
            #else
                BLINKER_LOG_ALL(BLINKER_F("ndef BLINKER_ARDUINOJSON"));

                heartBeat(_data);
                getVersion(_data);

                json_parse(_data);

                ahrs(Yaw, _data);
                gps(LONG, _data);
            #endif

            if (_fresh)
            {
                BProto::isParsed();
            }
            else
            {
                #if defined(BLINKER_PRO)
                    if (_parseFunc) {
                        if(_parseFunc(root)) {
                            _fresh = true;
                            BProto::isParsed();
                        }
                        
                        BLINKER_LOG_ALL(BLINKER_F("run parse callback function"));
                    }
                #endif
            }
        }        
    }
    else
    {
        #if defined(BLINKER_ARDUINOJSON)
            String arrayData = BLINKER_F("{\"data\":");
            arrayData += _data;
            arrayData += BLINKER_F("}");
            DynamicJsonBuffer jsonBuffer;
            JsonObject& root = jsonBuffer.parseObject(arrayData);

            if (!root.success()) return;

            arrayData = root["data"][0].as<String>();

            if (arrayData.length())
            {
                for (uint8_t a_num = 0; a_num < BLINKER_MAX_WIDGET_SIZE; a_num++)
                {
                    arrayData = root["data"][a_num].as<String>();

                    if(arrayData.length()) {
                        DynamicJsonBuffer _jsonBuffer;
                        JsonObject& _array = _jsonBuffer.parseObject(arrayData);

                        json_parse(_array);
                        #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
                            defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                            timerManager(_array, true);
                        #endif
                    }
                    else {
                        return;
                    }
                }
            }
            else {
                JsonObject& root = jsonBuffer.parseObject(_data);

                if (!root.success()) return;

                json_parse(root);
            }
        #else
            json_parse(_data);
        #endif
    }
}

void BlinkerApi::print()
{
    String _msg = BLINKER_F("");

    // checkFormat();
    // strcpy(_sendBuf, _msg.c_str());
    // _print(_sendBuf);
    // free(_sendBuf);
    // autoFormat = false;
    BProto::print(_msg);
}

template <typename T>
void BlinkerApi::print(T n)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n);
    _msg += BLINKER_F("\"");

    // checkFormat();
    // strcpy(_sendBuf, _msg.c_str());
    // _print(_sendBuf);
    // free(_sendBuf);
    // autoFormat = false;
    BProto::print(_msg);
}

template <typename T1, typename T2, typename T3>
void BlinkerApi::print(T1 n1, T2 n2, T3 n3)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":\"");
    _msg += STRING_format(n2);
    _msg += BLINKER_CMD_INTERSPACE;
    _msg += STRING_format(n3);
    _msg += BLINKER_F("\"");

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::printArray(T1 n1, const String &s2)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":");
    _msg += s2;
    
    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::printObject(T1 n1, const String &s2)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":");
    _msg += s2;
    
    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::print(T1 n1, const String &s2)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":\"");
    _msg += s2;
    _msg += BLINKER_F("\"");

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::print(T1 n1, const char str2[])
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":\"");
    _msg += STRING_format(str2);
    _msg += BLINKER_F("\"");

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::print(T1 n1, char c)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":");
    _msg += STRING_format(c);

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::print(T1 n1, unsigned char b)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":");
    _msg += STRING_format(b);

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::print(T1 n1, int n)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":");
    _msg += STRING_format(n);

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::print(T1 n1, unsigned int n)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":");
    _msg += STRING_format(n);

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::print(T1 n1, long n)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":");
    _msg += STRING_format(n);

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::print(T1 n1, unsigned long n)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":");
    _msg += STRING_format(n);

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T1>
void BlinkerApi::print(T1 n1, double n)
{
    String _msg = BLINKER_F("\"");
    _msg += STRING_format(n1);
    _msg += BLINKER_F("\":");
    _msg += STRING_format(n);

    // checkFormat();
    // autoFormatData(STRING_format(n1), _msg);
    // autoFormatFreshTime = millis();
    BProto::print(STRING_format(n1), _msg);
}

template <typename T>
void BlinkerApi::notify(T n)
{    
    print(BLINKER_CMD_NOTICE, STRING_format(n));
}

void BlinkerApi::vibrate(uint16_t ms)
{
    if (ms > 1000) ms = 1000;

    print(BLINKER_CMD_VIBRATE, ms);
}

void BlinkerApi::delay(unsigned long ms)
{
    uint32_t start = micros();
    uint32_t __start = millis();
    unsigned long _ms = ms;
    while (ms > 0)
    {
        run();

        if ((micros() - start) >= 1000)
        {
            ms -= 1;
            start += 1000;
        }

        if ((millis() - __start) >= _ms)
        {
            ms = 0;
        }

        yield();
    }
}

void BlinkerApi::attachAhrs()
{
    bool state = false;
    uint32_t startTime = millis();
    print(BLINKER_CMD_AHRS, BLINKER_CMD_ON);
    while (!state)
    {
        while (!BProto::connected())
        {
            run();
            if (BProto::connect())
            {
                print(BLINKER_CMD_AHRS, BLINKER_CMD_ON);
                BProto::printNow();
                break;
            }
        }

        ::delay(100);

        if (BProto::checkAvail())
        {
            if (STRING_contains_string(BProto::dataParse(), BLINKER_CMD_AHRS))
            {
                BLINKER_LOG(BLINKER_F("AHRS attach sucessed..."));
                // parse(BProto::dataParse());
                state = true;
                break;
            }
            else
            {
                BLINKER_LOG(BLINKER_F("AHRS attach failed...Try again"));
                startTime = millis();
                // parse(BProto::dataParse());
                print(BLINKER_CMD_AHRS, BLINKER_CMD_ON);
                BProto::printNow();
            }
        }
        else
        {
            if (millis() - startTime > BLINKER_CONNECT_TIMEOUT_MS)
            {
                BLINKER_LOG(BLINKER_F("AHRS attach failed...Try again"));
                startTime = millis();
                print(BLINKER_CMD_AHRS, BLINKER_CMD_ON);
                BProto::printNow();
            }
        }
    }
}

void BlinkerApi::detachAhrs()
{
    print(BLINKER_CMD_AHRS, BLINKER_CMD_OFF);
    ahrsValue[Yaw] = 0;
    ahrsValue[Roll] = 0;
    ahrsValue[Pitch] = 0;
}

float BlinkerApi::gps(b_gps_t axis)
{
    if ((millis() - gps_get_time) >= BLINKER_GPS_MSG_LIMIT || \
        gps_get_time == 0)
    {
        print(BLINKER_CMD_GET, BLINKER_CMD_GPS);
        BProto::printNow();
        delay(100);
    }

    return gpsValue[axis]*1000000;
}

#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)    
    void BlinkerApi::setTimezone(float tz)
    {
        _timezone = tz;
        _isNTPInit = false;
    }
    
    int8_t BlinkerApi::second()
    {
        if (_isNTPInit)
        {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return timeinfo.tm_sec;
        }
        return -1;
    }
    /**< seconds after the minute - [ 0 to 59 ] */
    
    int8_t BlinkerApi::minute()
    {
        if (_isNTPInit) {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return timeinfo.tm_min;
        }
        return -1;
    }
    /**< minutes after the hour - [ 0 to 59 ] */
    
    int8_t BlinkerApi::hour()
    {
        if (_isNTPInit)
        {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return timeinfo.tm_hour;
        }
        return -1;
    }
    /**< hours since midnight - [ 0 to 23 ] */
    
    int8_t BlinkerApi::mday()
    {
        if (_isNTPInit)
        {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return timeinfo.tm_mday;
        }
        return -1;
    }
    /**< day of the month - [ 1 to 31 ] */
    
    int8_t BlinkerApi::wday()
    {
        if (_isNTPInit)
        {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return timeinfo.tm_wday;
        }
        return -1;
    }
    /**< days since Sunday - [ 0 to 6 ] */
    
    int8_t BlinkerApi::month()
    {
        if (_isNTPInit) {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return timeinfo.tm_mon + 1;
        }
        return -1;
    }
    /**< months since January - [ 1 to 12 ] */
    
    int16_t BlinkerApi::year()
    {
        if (_isNTPInit)
        {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return timeinfo.tm_year + 1900;
        }
        return -1;
    }
    /**< years since 1900 */
    
    int16_t BlinkerApi::yday()
    {
        if (_isNTPInit)
        {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return timeinfo.tm_yday + 1;
        }
        return -1;
    }
    /**< days since January 1 - [ 1 to 366 ] */
    
    time_t  BlinkerApi::time()
    {
        if (_isNTPInit)
        {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return now_ntp;
        }
        return millis();
    }

    
    int32_t BlinkerApi::dtime()
    {
        if (_isNTPInit)
        {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            return timeinfo.tm_hour * 60 * 60 + timeinfo.tm_min * 60 + timeinfo.tm_sec;
        }
        return -1;
    }

    template<typename T>
    bool BlinkerApi::sms(const T& msg)
    {
        String _msg = STRING_format(msg);

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += BProto::deviceName();
            data += BLINKER_F("\",\"key\":\"");
            data += BProto::authKey();
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #elif defined(BLINKER_WIFI)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += macDeviceName();
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #endif

        if (_msg.length() > 20) {
            return false;
        }

        return (blinkerServer(BLINKER_CMD_SMS_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
    }

    template<typename T>
    bool BlinkerApi::sms(const T& msg, const char* cel)
    {
        String _msg = STRING_format(msg);

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += BProto::deviceName();
            data += BLINKER_F("\",\"key\":\"");
            data += BProto::authKey();
            data += BLINKER_F("\",\"cel\":\"");
            data += cel;
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #elif defined(BLINKER_WIFI)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += macDeviceName();
            data += BLINKER_F("\",\"cel\":\"");
            data += cel;
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #endif

        if (_msg.length() > 20) {
            return false;
        }

        return (blinkerServer(BLINKER_CMD_SMS_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
    }

    template<typename T>
    bool BlinkerApi::push(const T& msg)
    {
        String _msg = STRING_format(msg);

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += BProto::deviceName();
            data += BLINKER_F("\",\"key\":\"");
            data += BProto::authKey();
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #elif defined(BLINKER_WIFI)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += macDeviceName();
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #endif

        return (blinkerServer(BLINKER_CMD_PUSH_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
    }

    template<typename T>
    bool BlinkerApi::wechat(const T& msg)
    {
        String _msg = STRING_format(msg);

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += BProto::deviceName();
            data += BLINKER_F("\",\"key\":\"");
            data += BProto::authKey();
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #elif defined(BLINKER_WIFI)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += macDeviceName();
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #endif

        return (blinkerServer(BLINKER_CMD_WECHAT_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
    }

    template<typename T>
    bool BlinkerApi::wechat(const String & title, const String & state, const T& msg)
    {
        String _msg = STRING_format(msg);

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += BProto::deviceName();
            data += BLINKER_F("\",\"key\":\"");
            data += BProto::authKey();
            data += BLINKER_F("\",\"title\":\"");
            data += title;
            data += BLINKER_F("\",\"state\":\"");
            data += state;
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #elif defined(BLINKER_WIFI)
            String data = BLINKER_F("{\"deviceName\":\"");
            data += macDeviceName();
            data += BLINKER_F("\",\"title\":\"");
            data += title;
            data += BLINKER_F("\",\"state\":\"");
            data += state;
            data += BLINKER_F("\",\"msg\":\"");
            data += _msg;
            data += BLINKER_F("\"}");
        #endif

        return (blinkerServer(BLINKER_CMD_WECHAT_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
    }
    
    String BlinkerApi::weather(const String & _city)
    {
        String data = BLINKER_F("/weather/now?");

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            data += BLINKER_F("deviceName=");
            data += BProto::deviceName();
            data += BLINKER_F("&key=");
            data += BProto::authKey();
        #elif defined(BLINKER_WIFI)
            data += BLINKER_F("deviceName=");
            data += macDeviceName();
        #endif

        if (_city != BLINKER_CMD_DEFAULT)
        {
            data += BLINKER_F("&location=");
            data += _city;
        }
        
        return blinkerServer(BLINKER_CMD_WEATHER_NUMBER, data);
    }
    
    String BlinkerApi::aqi(const String & _city)
    {
        String data = BLINKER_F("/weather/aqi?");

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            data += BLINKER_F("deviceName=");
            data += BProto::deviceName();
            data += BLINKER_F("&key=");
            data += BProto::authKey();
        #elif defined(BLINKER_WIFI)
            data += BLINKER_F("deviceName=");
            data += macDeviceName();
        #endif

        if (_city != BLINKER_CMD_DEFAULT)
        {
            data += BLINKER_F("&location=");
            data += _city;
        }
        
        return blinkerServer(BLINKER_CMD_AQI_NUMBER, data);
    }
    
    void BlinkerApi::loadTimer()
    {
        BLINKER_LOG(BLINKER_F(
            "\n==========================================================="
            "\n================== Blinker Timer loaded! =================="
            "\nWarning!EEPROM address 1536-2431 is used for Blinker Timer!"
            "\n============= DON'T USE THESE EEPROM ADDRESS! ============="
            "\n===========================================================\n"));

        checkTimerErase();
        loadCountdown();
        loadLoop();
    }
    
    void BlinkerApi::deleteTimer()
    {
        EEPROM.begin(BLINKER_EEP_SIZE);

        EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, 0);
        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, 0);
        EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, 0);

        EEPROM.commit();
        EEPROM.end();
    }
    
    void BlinkerApi::deleteCountdown()
    {
        EEPROM.begin(BLINKER_EEP_SIZE);

        EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, 0);

        EEPROM.commit();
        EEPROM.end();
    }
    
    void BlinkerApi::deleteLoop()
    {
        EEPROM.begin(BLINKER_EEP_SIZE);

        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, 0);

        EEPROM.commit();
        EEPROM.end();
    }
    
    void BlinkerApi::deleteTiming()
    {
        EEPROM.begin(BLINKER_EEP_SIZE);

        EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, 0);

        EEPROM.commit();
        EEPROM.end();
    }

    template<typename T>
    bool BlinkerApi::configUpdate(const T& msg)
    {
        String _msg = STRING_format(msg);

        String data = BLINKER_F("{\"deviceName\":\"");
        data += BProto::deviceName();
        data += BLINKER_F("\",\"key\":\"");
        data += BProto::authKey();
        data += BLINKER_F("\",\"config\":\"");
        data += _msg;
        data += BLINKER_F("\"}");

        if (_msg.length() > 256) return false;
        
        return (blinkerServer(BLINKER_CMD_CONFIG_UPDATE_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
    }

    
    String BlinkerApi::configGet()
    {
        String data = BLINKER_F("/pull_userconfig?deviceName=");
        data += BProto::deviceName();
        data += BLINKER_F("&key=");
        data += BProto::authKey();

        return blinkerServer(BLINKER_CMD_CONFIG_GET_NUMBER, data);
    }

    
    bool BlinkerApi::configDelete()
    {
        String data = BLINKER_F("/delete_userconfig?deviceName=");
        data += BProto::deviceName();
        data += BLINKER_F("&key=");
        data += BProto::authKey();

        return (blinkerServer(BLINKER_CMD_CONFIG_DELETE_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
    }

    template<typename T>
    void BlinkerApi::dataStorage(char _name[], const T& msg)
    {
        String _msg = STRING_format(msg);

        int8_t num = checkNum(_name, _Data, data_dataCount);

        BLINKER_LOG_ALL(BLINKER_F("dataStorage num: "), num);
        
        if( num == BLINKER_OBJECT_NOT_AVAIL )
        {
            if (data_dataCount == BLINKER_MAX_BLINKER_DATA_SIZE)
            {
                return;
            }
            _Data[data_dataCount] = new BlinkerData();
            _Data[data_dataCount]->name(_name);
            // _Data[data_dataCount]->saveData(time(), _msg);
            _Data[data_dataCount]->saveData(_msg);
            data_dataCount++;
        }
        else {
            // _Data[num]->saveData(time(), _msg);
            _Data[num]->saveData(_msg);
        }
        
        BLINKER_LOG_ALL(_name, BLINKER_F(" save: "), _msg);
        BLINKER_LOG_ALL(BLINKER_F("data_dataCount: "), data_dataCount);
    }

    
    bool BlinkerApi::dataUpdate()
    {
        String data = BLINKER_F("{\"deviceName\":\"");
        data += BProto::deviceName();
        data += BLINKER_F("\",\"key\":\"");
        data += BProto::authKey();
        data += BLINKER_F("\",\"data\":{");
        // String _sdata;

        if (!data_dataCount) {
            BLINKER_ERR_LOG(BLINKER_F("none data storaged!"));
            return false;
        }

        uint32_t now_time = time();

        for (uint8_t _num = 0; _num < data_dataCount; _num++) {
            data += BLINKER_F("\"");
            data += _Data[_num]->getName();
            data += BLINKER_F("\":");
            data += _Data[_num]->getData(now_time);
            if (_num < data_dataCount - 1) {
                data += BLINKER_F(",");
            }
            
            BLINKER_LOG_ALL(BLINKER_F("num: "), _num, \
                    BLINKER_F(" name: "), _Data[_num]->getName());
        }

        data += BLINKER_F("}}");

        BLINKER_LOG_ALL(BLINKER_F("dataUpdate: "), data);

        // return true;
                        //  + \ _msg + 
                        // "\"}}";

        if (blinkerServer(BLINKER_CMD_DATA_STORAGE_NUMBER, data) == BLINKER_CMD_FALSE)
        {
            for (uint8_t _num = 0; _num < data_dataCount; _num++)
            {
                delete _Data[_num];
            }
            data_dataCount = 0;

            return false;
        }
        else
        {
            for (uint8_t _num = 0; _num < data_dataCount; _num++)
            {
                delete _Data[_num];
            }
            data_dataCount = 0;

            return true;
        }
    }

    
    String BlinkerApi::dataGet()
    {
        String data = BLINKER_F("/pull_cloudStorage?deviceName=");
        data += BProto::deviceName();
        data += BLINKER_F("&key=");
        data += BProto::authKey();

        return blinkerServer(BLINKER_CMD_DATA_GET_NUMBER, data);
    }

    
    String BlinkerApi::dataGet(const String & _type)
    {
        String data = BLINKER_F("/pull_cloudStorage?deviceName=");
        data += BProto::deviceName();
        data += BLINKER_F("&key=");
        data += BProto::authKey();
        data += BLINKER_F("&dataType=");
        data += _type;

        return blinkerServer(BLINKER_CMD_DATA_GET_NUMBER, data);
    }

    
    String BlinkerApi::dataGet(const String & _type, const String & _date)
    {
        String data = BLINKER_F("/pull_cloudStorage?deviceName=");
        data += BProto::deviceName();
        data += BLINKER_F("&key=");
        data += BProto::authKey();
        data += BLINKER_F("&dataType=");
        data += _type;
        data += BLINKER_F("&date=");
        data += _date;

        return blinkerServer(BLINKER_CMD_DATA_GET_NUMBER, data);
    }

    
    bool BlinkerApi::dataDelete()
    {
        String data = BLINKER_F("/delete_cloudStorage?deviceName=");
        data += BProto::deviceName();
        data += BLINKER_F("&key=");
        data += BProto::authKey();

        return (blinkerServer(BLINKER_CMD_DATA_DELETE_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
    }

    
    bool BlinkerApi::dataDelete(const String & _type)
    {
        String data = BLINKER_F("/delete_cloudStorage?deviceName=");
        data += BProto::deviceName();
        data += BLINKER_F("&key=");
        data += BProto::authKey();
        data += BLINKER_F("&dataType=");
        data += _type;

        return (blinkerServer(BLINKER_CMD_DATA_DELETE_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
    }

    
    bool BlinkerApi::autoPull()
    {
        String data = BLINKER_F("/auto/pull?deviceName=");
        data += BProto::deviceName();
        data += BLINKER_F("&key=");
        data += BProto::authKey();

        String payload = blinkerServer(BLINKER_CMD_AUTO_PULL_NUMBER, data);

        if (payload == BLINKER_CMD_FALSE)
        {
            return false;
        }
        else
        {
            DynamicJsonBuffer jsonBuffer;
            JsonObject& autoJson = jsonBuffer.parseObject(payload);

            return autoManager(autoJson);
        }
    }

    
    void BlinkerApi::autoInput(const String & key, const String & state)
    {
        if (!_isNTPInit) return;

        int32_t nowTime = dtime();

        for (uint8_t _num = 0; _num < _aCount; _num++)
        {
            _AUTO[_num]->run(key, state, nowTime);
        }
    }

    
    void BlinkerApi::autoInput(const String & key, float data)
    {
        if (!_isNTPInit) return;

        int32_t nowTime = dtime();

        for (uint8_t _num = 0; _num < _aCount; _num++)
        {
            _AUTO[_num]->run(key, data, nowTime);
        }
    }

    
    void BlinkerApi::autoRun()
    {
        for (uint8_t _num = 0; _num < _aCount; _num++)
        {
            if (_AUTO[_num]->isTrigged())
            {
                // if (autoTrigged(_AUTO[_num]->id()))
                // {
                //     BLINKER_LOG_ALL(BLINKER_F("trigged sucessed"));

                //     _AUTO[_num]->fresh();
                // }
                // else
                // {
                //     BLINKER_LOG_ALL(BLINKER_F("trigged failed"));
                // }
            }
        }
    }

    
    void BlinkerApi::freshAttachBridge(char _key[], blinker_callback_with_string_arg_t _func)
    {
        int8_t num = checkNum(_key, _Bridge, _bridgeCount);
        if(num >= 0 ) _Bridge[num]->setFunc(_func);
    }

    
    uint8_t BlinkerApi::attachBridge(char _key[], blinker_callback_with_string_arg_t _func)
    {
        int8_t num = checkNum(_key, _Bridge, _bridgeCount);

        if (num == BLINKER_OBJECT_NOT_AVAIL)
        {
            if (_bridgeCount < BLINKER_MAX_BRIDGE_SIZE)
            {
                _Bridge[_bridgeCount] = new BlinkerBridge_key(_key, _func);
                _bridgeCount++;
                
                BLINKER_LOG_ALL(BLINKER_F("new bridgeKey: "), _key, \
                            BLINKER_F(" _bridgeCount: "), _bridgeCount);
                return _bridgeCount;
            }
            else
            {
                return 0;
            }
        }
        else if(num >= 0 )
        {
            BLINKER_ERR_LOG(BLINKER_F("bridgeKey > "), _key, \
                    BLINKER_F(" < has been registered, please register another name!"));
            return 0;
        }
        else
        {
            return 0;
        }
    }

    
    char * BlinkerApi::bridgeKey(uint8_t num)
    {
        if (num) return _Bridge[num - 1]->getKey();
        else return NULL;
    }

    
    char * BlinkerApi::bridgeName(uint8_t num)
    {
        if (num) return _Bridge[num - 1]->getName();
        else return NULL;
    }

    
    void BlinkerApi::bridgeInit()
    {
        String register_r;
        for (uint8_t num = 0; num < _bridgeCount; num++)
        {
            register_r = bridgeQuery(_Bridge[num]->getKey());
            BLINKER_LOG_ALL(BLINKER_F("bridgeQuery name: "), register_r);
            if (strcmp(register_r.c_str(), BLINKER_CMD_FALSE) != 0)
            {
                _Bridge[num]->name(register_r);
            }
        }
    }

    void BlinkerApi::bridgePrint(char * bName, const String & data)
    {
        BProto::bPrint(bName, data);
    }
    
    void BlinkerApi::aligeniePrint(String & _msg)
    {
        BLINKER_LOG_ALL(BLINKER_F("response to AliGenie: "), _msg);

        // BProto::aliPrint(_msg);

        if (_msg.length() <= BLINKER_MAX_SEND_SIZE)
        {
            // char* aliData = (char*)malloc((_msg.length()+1+128)*sizeof(char));
            // memcpy(aliData, '\0', _msg.length()+128);
            // strcpy(aliData, _msg.c_str());
            BProto::aliPrint(_msg);
            // free(aliData);
        }
        else
        {
            BLINKER_ERR_LOG(BLINKER_F("SEND DATA BYTES MAX THAN LIMIT!"));
        }
    }

    void BlinkerApi::duerPrint(String & _msg)
    {
        BLINKER_LOG_ALL(BLINKER_F("response to DuerOS: "), _msg);

        // BProto::aliPrint(_msg);

        if (_msg.length() <= BLINKER_MAX_SEND_SIZE)
        {
            // char* aliData = (char*)malloc((_msg.length()+1+128)*sizeof(char));
            // memcpy(aliData, '\0', _msg.length()+128);
            // strcpy(aliData, _msg.c_str());
            BProto::duerPrint(_msg);
            // free(aliData);
        }
        else
        {
            BLINKER_ERR_LOG(BLINKER_F("SEND DATA BYTES MAX THAN LIMIT!"));
        }
    }

    
    void BlinkerApi::loadOTA()
    {
        // if (_OTA.loadOTACheck())
        // {
        //     if (!_OTA.loadVersion())
        //     {
        //         _OTA.saveVersion();
        //     }
        // }

        BLINKER_LOG_ALL(BLINKER_F("OTA load: "), BLINKER_OTA_VERSION_CODE);

        if (_OTA.loadOTACheck() == BLINKER_OTA_RUN)
        {
            _OTA.saveOTACheck();
            updateOTAStatus(10, "download firmware");

            String otaData = checkOTA();

            if (otaData != BLINKER_CMD_FALSE)
            {
                DynamicJsonBuffer jsonBuffer;
                JsonObject& otaJson = jsonBuffer.parseObject(otaData);

                if (!otaJson.success())
                {
                    BLINKER_ERR_LOG_ALL(BLINKER_F("check ota data error"));
                    return;
                }

                String otaHost = otaJson["host"];
                String otaUrl = otaJson["url"];
                String otaFp = otaJson["fingerprint"];

                _OTA.config(otaHost, otaUrl, otaFp);

                if (_OTA.update())
                {
                    // _OTA.saveVersion();
                    // _OTA.clearOTACheck();

                    // updateOTAStatus(100);

                    BProto::freshAlive();
                    otaStatus(99, BLINKER_F("Firmware download sucessed"));
                    updateOTAStatus(99, BLINKER_F("Firmware download sucessed"));
                    ESP.restart();
                }
                else
                {
                    _OTA.clearOTACheck();

                    BProto::freshAlive();
                    otaStatus(-2, BLINKER_F("Firmware download failed"));
                    updateOTAStatus(-2, BLINKER_F("Firmware download failed"));
                }
            }
        }
        else if (_OTA.loadOTACheck() == BLINKER_OTA_START)
        {
            if (!_OTA.loadVersion())
            {
                _OTA.saveVersion();
                _OTA.clearOTACheck();

                BProto::freshAlive();
                otaStatus(100, BLINKER_F("Firmware update success"));
                updateOTAStatus(100, BLINKER_F("Firmware update success"));
                // ota failed
            }
            else
            {
                // _OTA.saveVersion();
                _OTA.clearOTACheck();
                
                BProto::freshAlive();
                otaStatus(-2, BLINKER_F("Firmware download failed"));
                updateOTAStatus(-2, BLINKER_F("Firmware download failed"));
                // ota success
            }
        }
        else if (_OTA.loadOTACheck() == BLINKER_OTA_CLEAR)
        {
            // _OTA.saveVersion();
            // _OTA.clearOTACheck();

            if (!_OTA.loadVersion()) _OTA.saveVersion();
        }        
        else
        {
            if (!_OTA.loadVersion())
            {
                if (_OTA.loadOTACheck() > 0)
                {
                    // updateOTAStatus(100);
                    _OTA.clearOTACheck();
                    _OTA.saveVersion();
                }
                else
                {
                    _OTA.saveVersion();
                }
            }
            else if (_OTA.loadVersion() && _OTA.loadOTACheck() == 0)
            {
                // updateOTAStatus(-2);
                _OTA.clearOTACheck();
            }
            else
            {
                _OTA.clearOTACheck();
            }
        }
        
    }

    
    void BlinkerApi::ota()
    {
        if (checkCanOTA())
        {
            _OTA.saveOTARun();

            // ::delay(100);
            // ESP.restart();

            loadOTA();
        }
    }

    
    String BlinkerApi::checkOTA()
    {
        String data = BLINKER_F("/ota/upgrade?deviceName=");// + 
        data += STRING_format(BProto::deviceName());

        return blinkerServer(BLINKER_CMD_OTA_NUMBER, data);
    }

    
    bool BlinkerApi::updateOTAStatus(int8_t status, const String & msg)
    {
        String data;

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            data = BLINKER_F("{\"deviceName\":\"");
            data += BProto::deviceName();
            data += BLINKER_F("\",\"key\":\"");
            data += BProto::authKey();
            data += BLINKER_F("\",\"upgrade\":true,\"upgradeData\":{\"step\":\"");
            data += STRING_format(status);
            data += BLINKER_F("\",\"desc\":\"");
            data += msg;
            data += BLINKER_F("\"}}");
        #elif defined(BLINKER_WIFI)
            return false;
        #endif

        return blinkerServer(BLINKER_CMD_OTA_STATUS_NUMBER, data) == BLINKER_CMD_FALSE;
    }

    
    void BlinkerApi::otaStatus(int8_t status, const String & msg)
    {
        String data;

        data = BLINKER_F("{\"step\":\"");
        data += STRING_format(status);
        data += BLINKER_F("\",\"desc\":\"");
        data += msg;
        data += BLINKER_F("\"}");

        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            print(BLINKER_CMD_VERSION, BLINKER_OTA_VERSION_CODE);
            print(BLINKER_CMD_STATE, BLINKER_CMD_ONLINE);
            printObject(BLINKER_F("upgradeData"), data);
            BProto::printNow();
        #endif
    }
#endif

void BlinkerApi::freshAttachWidget(char _name[], blinker_callback_with_string_arg_t _func)
{
    int8_t num = checkNum(_name, _Widgets_str, _wCount_str);
    if(num >= 0 ) _Widgets_str[num]->setFunc(_func);
}

#if defined(BLINKER_BLE)
    void BlinkerApi::freshAttachWidget(char _name[], blinker_callback_with_joy_arg_t _func)
    {
        int8_t num = checkNum(_name, _Widgets_joy, _wCount_joy);
        if(num >= 0 ) _Widgets_joy[num]->setFunc(_func);
    }
#endif

void BlinkerApi::freshAttachWidget(char _name[], blinker_callback_with_rgb_arg_t _func)
{
    int8_t num = checkNum(_name, _Widgets_rgb, _wCount_rgb);
    if(num >= 0 ) _Widgets_rgb[num]->setFunc(_func);
}

void BlinkerApi::freshAttachWidget(char _name[], blinker_callback_with_int32_arg_t _func)
{
    int8_t num = checkNum(_name, _Widgets_int, _wCount_int);
    if(num >= 0 ) _Widgets_int[num]->setFunc(_func);
}

uint8_t BlinkerApi::attachWidget(char _name[], blinker_callback_with_string_arg_t _func)
{
    int8_t num = checkNum(_name, _Widgets_str, _wCount_str);

    if (num == BLINKER_OBJECT_NOT_AVAIL)
    {
        if (_wCount_str < BLINKER_MAX_WIDGET_SIZE*2)
        {
            _Widgets_str[_wCount_str] = new BlinkerWidgets_string(_name, _func);
            _wCount_str++;
            
            BLINKER_LOG_ALL(BLINKER_F("new widgets: "), _name, \
                        BLINKER_F(" _wCount_str: "), _wCount_str);
            return _wCount_str;
        }
        else
        {
            return 0;
        }
    }
    else if(num >= 0 )
    {
        BLINKER_ERR_LOG(BLINKER_F("widgets name > "), _name, \
                BLINKER_F(" < has been registered, please register another name!"));
        return 0;
    }
    else
    {
        return 0;
    }
}

#if defined(BLINKER_BLE)
    uint8_t BlinkerApi::attachWidget(char _name[], blinker_callback_with_joy_arg_t _func)
    {
        int8_t num = checkNum(_name, _Widgets_joy, _wCount_joy);
        if (num == BLINKER_OBJECT_NOT_AVAIL)
        {
            if (_wCount_joy < BLINKER_MAX_WIDGET_SIZE/2)
            {
                _Widgets_joy[_wCount_joy] = new BlinkerWidgets_joy(_name, _func);
                _wCount_joy++;

                BLINKER_LOG_ALL(BLINKER_F("new widgets: "), _name, \
                BLINKER_F(" _wCount_joy: "), _wCount_joy);

                return _wCount_joy;
            }
            else
            {
                return 0;
            }
        }
        else if(num >= 0 )
        {
            BLINKER_ERR_LOG(BLINKER_F("widgets name > "), _name, \
                    BLINKER_F(" < has been registered, please register another name!"));
            return 0;
        }
        else
        {
            return 0;
        }
    }
#endif

uint8_t BlinkerApi::attachWidget(char _name[], blinker_callback_with_rgb_arg_t _func)
{
    int8_t num = checkNum(_name, _Widgets_rgb, _wCount_rgb);
    if (num == BLINKER_OBJECT_NOT_AVAIL)
    {
        if (_wCount_rgb < BLINKER_MAX_WIDGET_SIZE/2)
        {
            _Widgets_rgb[_wCount_rgb] = new BlinkerWidgets_rgb(_name, _func);
            _wCount_rgb++;
            
            BLINKER_LOG_ALL(BLINKER_F("new widgets: "), _name, \
                        BLINKER_F(" _wCount_rgb: "), _wCount_rgb);

            return _wCount_rgb;
        }
        else
        {
            return 0;
        }
    }
    else if(num >= 0 )
    {
        BLINKER_ERR_LOG(BLINKER_F("widgets name > "), _name, \
                BLINKER_F(" < has been registered, please register another name!"));
        return 0;
    }
    else
    {
        return 0;
    }
}

uint8_t BlinkerApi::attachWidget(char _name[], blinker_callback_with_int32_arg_t _func)
{
    int8_t num = checkNum(_name, _Widgets_int, _wCount_int);
    if (num == BLINKER_OBJECT_NOT_AVAIL)
    {
        if (_wCount_int < BLINKER_MAX_WIDGET_SIZE*2)
        {
            _Widgets_int[_wCount_int] = new BlinkerWidgets_int32(_name, _func);
            _wCount_int++;

            BLINKER_LOG_ALL(BLINKER_F("new widgets: "), _name, \
                        BLINKER_F(" _wCount_int: "), _wCount_int);

            return _wCount_int;
        }
        else
        {
            return 0;
        }
    }
    else if(num >= 0 )
    {
        BLINKER_ERR_LOG(BLINKER_F("widgets name > "), _name, \
                BLINKER_F(" < has been registered, please register another name!"));
        return 0;
    }
    else
    {
        return 0;
    }
}

void BlinkerApi::attachSwitch(blinker_callback_with_string_arg_t _func)
{
    // if (!_BUILTIN_SWITCH)
    // {
    //     _BUILTIN_SWITCH = new BlinkerWidgets_string(BLINKER_CMD_BUILTIN_SWITCH, _func);
    // }
    // else
    // {
    //     _BUILTIN_SWITCH->setFunc(_func);
    // }

    _BUILTIN_SWITCH.setFunc(_func);
}

char * BlinkerApi::widgetName_str(uint8_t num)
{
    if (num) return _Widgets_str[num - 1]->getName();
    else return NULL;
}

#if defined(BLINKER_BLE)
    char * BlinkerApi::widgetName_joy(uint8_t num)
    {
        if (num) return _Widgets_joy[num - 1]->getName();
        else return NULL;
    }
#endif

char * BlinkerApi::widgetName_rgb(uint8_t num)
{
    if (num) return _Widgets_rgb[num - 1]->getName();
    else return NULL;
}

char * BlinkerApi::widgetName_int(uint8_t num)
{
    if (num) return _Widgets_int[num - 1]->getName();
    else return NULL;
}

#if defined(BLINKER_ARDUINOJSON)
    int16_t BlinkerApi::ahrs(b_ahrsattitude_t attitude, const JsonObject& data)
    {
        if (data.containsKey(BLINKER_CMD_AHRS)) {
            int16_t aAttiValue = data[BLINKER_CMD_AHRS][attitude];
            ahrsValue[Yaw] = data[BLINKER_CMD_AHRS][Yaw];
            ahrsValue[Roll] = data[BLINKER_CMD_AHRS][Roll];
            ahrsValue[Pitch] = data[BLINKER_CMD_AHRS][Pitch];

            _fresh = true;

            return aAttiValue;
        }
        else {
            return ahrsValue[attitude];
        }
    }

    float BlinkerApi::gps(b_gps_t axis, const JsonObject& data)
    {
        // if (((millis() - gps_get_time) >= BLINKER_GPS_MSG_LIMIT || 
        //     gps_get_time == 0) && !newData)
        // {
        //     static_cast<Proto*>(this)->print(BLINKER_CMD_GET, BLINKER_CMD_GPS);
        //     static_cast<Proto*>(this)->printNow();
        //     delay(100);
        // }

        if (data.containsKey(BLINKER_CMD_GPS)) {
            String gpsValue_LONG = data[BLINKER_CMD_GPS][LONG];
            String gpsValue_LAT = data[BLINKER_CMD_GPS][LAT];
            gpsValue[LONG] = gpsValue_LONG.toFloat();
            gpsValue[LAT] = gpsValue_LAT.toFloat();

            _fresh = true;

            if (_fresh) {
                BProto::isParsed();
                gps_get_time = millis();
            }

            return gpsValue[axis]*1000000;
        }
        else {
            return gpsValue[axis]*1000000;
        }
    }

    void BlinkerApi::heartBeat(const JsonObject& data)
    {
        String state = data[BLINKER_CMD_GET];

        if (state.length())
        {
            if (state == BLINKER_CMD_STATE)
            {
                #if defined(BLINKER_BLE) || defined(BLINKER_WIFI)
                    print(BLINKER_CMD_STATE, BLINKER_CMD_CONNECTED);
                #else
                    print(BLINKER_CMD_STATE, BLINKER_CMD_ONLINE);
                #endif

                #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
                    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                    String _timer = taskCount ? "1":"0";
                    _timer += _cdState ? "1":"0";
                    _timer += _lpState ? "1":"0";

                    BLINKER_LOG_ALL(BLINKER_F("timer codes: "), _timer);

                    print(BLINKER_CMD_TIMER, _timer);
                    // static_cast<Proto*>(this)->printJson(timerSetting());

                    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || \
                        defined(BLINKER_AT_MQTT)
                        print(BLINKER_CMD_VERSION, BLINKER_OTA_VERSION_CODE);
                    #endif
                #endif

                if (_heartbeatFunc) {
                    _heartbeatFunc();
                }

                if (_summaryFunc) {
                    String summary_data = _summaryFunc();
                    if (summary_data.length()) {
                        summary_data = summary_data.substring(0, BLINKER_MAX_SUMMARY_DATA_SIZE);

                        BLINKER_LOG_ALL(BLINKER_F("summary_data: "), summary_data);

                        print(BLINKER_CMD_SUMMARY, summary_data);
                    }
                }

                BProto::checkState(false);
                BProto::printNow();
                _fresh = true;

                // #if defined(BLINKER_AT_MQTT)
                //     atHeartbeat();
                // #endif
            }
        }
    }

    void BlinkerApi::getVersion(const JsonObject& data)
    {
        String state = data[BLINKER_CMD_GET];
        
        if (state.length())
        {
            if (state == BLINKER_CMD_VERSION)
            {
                print(BLINKER_CMD_VERSION, "0.1.0");
                _fresh = true;
            }
        }
    }

    void BlinkerApi::setSwitch(const JsonObject& data)
    {
        String state = data[BLINKER_CMD_BUILTIN_SWITCH];

        if (state.length())
        {
            // if (_BUILTIN_SWITCH)
            // {
            //     blinker_callback_with_string_arg_t sFunc = _BUILTIN_SWITCH->getFunc();

            //     if (sFunc) sFunc(state);
            // }
            blinker_callback_with_string_arg_t sFunc = _BUILTIN_SWITCH.getFunc();

            if (sFunc) sFunc(state);
            _fresh = true;
        }
    }

    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        void BlinkerApi::bridgeParse(char * _bName, const JsonObject& data)
        {
            // int8_t num = checkNum(_bName, _Bridge, _bridgeCount);

            // if (num == BLINKER_OBJECT_NOT_AVAIL ||
            //     !data.containsKey(BLINKER_CMD_FROMDEVICE))
            // {
            //     return;
            // }
            
            // String _name = data[BLINKER_CMD_FROMDEVICE];

            // // if (data.containsKey(_bName))
            // if (_name == _bName)
            // {
            //     String state = data[BLINKER_CMD_DATA];//[_bName];

            //     _fresh = true;
                
            //     BLINKER_LOG_ALL(BLINKER_F("bridgeParse: "), _bName);

            //     blinker_callback_with_string_arg_t nbFunc = _Bridge[num]->getFunc();
                
            //     if (nbFunc) nbFunc(state);
            // }
        }
    #endif

    void BlinkerApi::strWidgetsParse(char _wName[], const JsonObject& data)
    {
        int8_t num = checkNum(_wName, _Widgets_str, _wCount_str);

        if (num == BLINKER_OBJECT_NOT_AVAIL) return;

        if (data.containsKey(_wName))
        {
            String state = data[_wName];

            _fresh = true;
            
            BLINKER_LOG_ALL(BLINKER_F("strWidgetsParse: "), _wName);

            blinker_callback_with_string_arg_t nbFunc = _Widgets_str[num]->getFunc();
            
            if (nbFunc) nbFunc(state);
        }
    }

    #if defined(BLINKER_BLE)
        void BlinkerApi::joyWidgetsParse(char _wName[], const JsonObject& data)
        {
            int8_t num = checkNum(_wName, _Widgets_joy, _wCount_joy);

            if (num == BLINKER_OBJECT_NOT_AVAIL) return;

            if (data.containsKey(_wName))
            {
                int16_t jxAxisValue = data[_wName][BLINKER_J_Xaxis];
                uint8_t jyAxisValue = data[_wName][BLINKER_J_Yaxis];

                _fresh = true;

                blinker_callback_with_joy_arg_t wFunc = _Widgets_joy[num]->getFunc();
                if (wFunc) wFunc(jxAxisValue, jyAxisValue);
            }
        }
    #endif

    void BlinkerApi::rgbWidgetsParse(char _wName[], const JsonObject& data)
    {
        int8_t num = checkNum(_wName, _Widgets_rgb, _wCount_rgb);

        if (num == BLINKER_OBJECT_NOT_AVAIL) return;

        if (data.containsKey(_wName))
        {
            uint8_t _rValue = data[_wName][BLINKER_R];
            uint8_t _gValue = data[_wName][BLINKER_G];
            uint8_t _bValue = data[_wName][BLINKER_B];
            uint8_t _brightValue = data[_wName][BLINKER_BRIGHT];

            _fresh = true;

            blinker_callback_with_rgb_arg_t wFunc = _Widgets_rgb[num]->getFunc();
            if (wFunc) wFunc(_rValue, _gValue, _bValue, _brightValue);
        }
    }

    void BlinkerApi::intWidgetsParse(char _wName[], const JsonObject& data)
    {
        int8_t num = checkNum(_wName, _Widgets_int, _wCount_int);

        if (num == BLINKER_OBJECT_NOT_AVAIL) return;

        if (data.containsKey(_wName)) {
            int _number = data[_wName];

            _fresh = true;

            blinker_callback_with_int32_arg_t wFunc = _Widgets_int[num]->getFunc();
            if (wFunc) {
                wFunc(_number);
            }
        }
    }

    void BlinkerApi::json_parse(const JsonObject& data)
    {
        setSwitch(data);

        for (uint8_t wNum = 0; wNum < _wCount_str; wNum++) {
            strWidgetsParse(_Widgets_str[wNum]->getName(), data);
        }
        for (uint8_t wNum_int = 0; wNum_int < _wCount_int; wNum_int++) {
            intWidgetsParse(_Widgets_int[wNum_int]->getName(), data);
        }
        for (uint8_t wNum_rgb = 0; wNum_rgb < _wCount_rgb; wNum_rgb++) {
            rgbWidgetsParse(_Widgets_rgb[wNum_rgb]->getName(), data);
        }
        #if defined(BLINKER_BLE)
            for (uint8_t wNum_joy = 0; wNum_joy < _wCount_joy; wNum_joy++) {
                joyWidgetsParse(_Widgets_joy[wNum_joy]->getName(), data);
            }
        #endif
    }

#else

    int16_t BlinkerApi::ahrs(b_ahrsattitude_t attitude, char data[])
    {
        int16_t aAttiValue = STRING_find_array_numberic_value(data, BLINKER_CMD_AHRS, attitude);

        if (aAttiValue != FIND_KEY_VALUE_FAILED)
        {
            ahrsValue[Yaw] = STRING_find_array_numberic_value(data, BLINKER_CMD_AHRS, Yaw);
            ahrsValue[Roll] = STRING_find_array_numberic_value(data, BLINKER_CMD_AHRS, Roll);
            ahrsValue[Pitch] = STRING_find_array_numberic_value(data, BLINKER_CMD_AHRS, Pitch);

            _fresh = true;

            return aAttiValue;
        }
        else {
            return ahrsValue[attitude];
        }
    }

    float BlinkerApi::gps(b_gps_t axis, char data[])
    {
        // if (((millis() - gps_get_time) >= BLINKER_GPS_MSG_LIMIT || 
        //     gps_get_time == 0) && !newData)
        // {
        //     static_cast<Proto*>(this)->print(BLINKER_CMD_GET, BLINKER_CMD_GPS);
        //     static_cast<Proto*>(this)->printNow();
        //     delay(100);
        // }

        String axisValue = STRING_find_array_string_value(data, BLINKER_CMD_GPS, axis);

        if (axisValue != "") {
            gpsValue[LONG] = STRING_find_array_string_value(data, BLINKER_CMD_GPS, LONG).toFloat();
            gpsValue[LAT] = STRING_find_array_string_value(data, BLINKER_CMD_GPS, LAT).toFloat();

            _fresh = true;

            if (_fresh) {
                BProto::isParsed();
                gps_get_time = millis();
            }

            return gpsValue[axis]*1000000;
        }
        else {
            return gpsValue[axis]*1000000;
        }
    }

    void BlinkerApi::heartBeat(char data[])
    {
        if (strstr(data, BLINKER_CMD_GET) && \
            strstr(data, BLINKER_CMD_STATE))
        {
            #if defined(BLINKER_BLE)
                print(BLINKER_CMD_STATE, BLINKER_CMD_CONNECTED);
            #else
                print(BLINKER_CMD_STATE, BLINKER_CMD_ONLINE);
            #endif

            if (_heartbeatFunc) {
                _heartbeatFunc();
            }

            if (_summaryFunc)
            {
                String summary_data = _summaryFunc();
                if (summary_data.length())
                {
                    summary_data = summary_data.substring(0, BLINKER_MAX_SUMMARY_DATA_SIZE);

                    BLINKER_LOG_ALL(BLINKER_F("summary_data: "), summary_data);

                    print(BLINKER_CMD_SUMMARY, summary_data);
                }
            }
            
            BProto::checkState(false);
            BProto::printNow();

            _fresh = true;

            // #if defined(BLINKER_AT_MQTT)
            //     static_cast<Proto*>(this)->atHeartbeat();
            // #endif
        }
    }

    void BlinkerApi::getVersion(char data[])
    {
        if (strstr(data, BLINKER_CMD_GET) && \
            strstr(data, BLINKER_CMD_VERSION))
        {
            print(BLINKER_CMD_VERSION, BLINKER_VERSION);
            _fresh = true;
        }
    }

    void BlinkerApi::setSwitch(char data[])
    {
        String state;

        if (STRING_find_string_value(data, state, BLINKER_CMD_BUILTIN_SWITCH))
        {
            // if (_BUILTIN_SWITCH)
            // {
            //     blinker_callback_with_string_arg_t sFunc = _BUILTIN_SWITCH->getFunc();

            //     if (sFunc) sFunc(state);
            // }
            blinker_callback_with_string_arg_t sFunc = _BUILTIN_SWITCH.getFunc();

            if (sFunc) sFunc(state);
            _fresh = true;
        }
    }

    void BlinkerApi::strWidgetsParse(char _wName[], char _data[])
    {
        int8_t num = checkNum(_wName, _Widgets_str, _wCount_str);

        if (num == BLINKER_OBJECT_NOT_AVAIL) return;

        String state;

        if (STRING_find_string_value(_data, state, _wName))
        {
            _fresh = true;

            blinker_callback_with_string_arg_t nbFunc = _Widgets_str[num]->getFunc();
            if (nbFunc) nbFunc(state);
        }
    }

    #if defined(BLINKER_BLE)
        void BlinkerApi::joyWidgetsParse(char _wName[], char _data[])
        {
            int8_t num = checkNum(_wName, _Widgets_joy, _wCount_joy);

            if (num == BLINKER_OBJECT_NOT_AVAIL) return;

            int16_t jxAxisValue = STRING_find_array_numberic_value(_data, \
                                                _wName, BLINKER_J_Xaxis);

            if (jxAxisValue != FIND_KEY_VALUE_FAILED)
            {
                uint8_t jyAxisValue = STRING_find_array_numberic_value(_data, \
                                                    _wName, BLINKER_J_Yaxis);

                _fresh = true;

                blinker_callback_with_joy_arg_t wFunc = _Widgets_joy[num]->getFunc();

                if (wFunc) wFunc(jxAxisValue, jyAxisValue);
            }
        }
    #endif

    void BlinkerApi::rgbWidgetsParse(char _wName[], char _data[])
    {
        int8_t num = checkNum(_wName, _Widgets_rgb, _wCount_rgb);

        if (num == BLINKER_OBJECT_NOT_AVAIL) return;

        int16_t _rValue = STRING_find_array_numberic_value(_data, \
                                                _wName, BLINKER_R);

        if (_rValue != FIND_KEY_VALUE_FAILED)
        {
            uint8_t _gValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_G);
            uint8_t _bValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_B);
            uint8_t _brightValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_BRIGHT);

            _fresh = true;

            blinker_callback_with_rgb_arg_t wFunc = _Widgets_rgb[num]->getFunc();

            if (wFunc) wFunc(_rValue, _gValue, _bValue, _brightValue);
        }
    }

    void BlinkerApi::intWidgetsParse(char _wName[], char _data[])
    {
        int8_t num = checkNum(_wName, _Widgets_int, _wCount_int);

        if (num == BLINKER_OBJECT_NOT_AVAIL) return;

        int _number = STRING_find_numberic_value(_data, _wName);

        if (_number != FIND_KEY_VALUE_FAILED)
        {
            _fresh = true;

            blinker_callback_with_int32_arg_t wFunc = _Widgets_int[num]->getFunc();

            if (wFunc) wFunc(_number);
        }
    }

    void BlinkerApi::json_parse(char _data[])
    {
        setSwitch(_data);        

        BLINKER_LOG_ALL("====_wCount_str: ", _wCount_str, " ====");

        for (uint8_t wNum = 0; wNum < _wCount_str; wNum++) {
            strWidgetsParse(_Widgets_str[wNum]->getName(), _data);
        }
        for (uint8_t wNum_int = 0; wNum_int < _wCount_int; wNum_int++) {
            intWidgetsParse(_Widgets_int[wNum_int]->getName(), _data);
        }
        for (uint8_t wNum_rgb = 0; wNum_rgb < _wCount_rgb; wNum_rgb++) {
            rgbWidgetsParse(_Widgets_rgb[wNum_rgb]->getName(), _data);
        }
        #if defined(BLINKER_BLE)
            for (uint8_t wNum_joy = 0; wNum_joy < _wCount_joy; wNum_joy++) {
                joyWidgetsParse(_Widgets_joy[wNum_joy]->getName(), _data);
            }
        #endif
    }
#endif

#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
    void BlinkerApi::beginAuto()
    {
        BLINKER_LOG(BLINKER_F("======================================================="));
        BLINKER_LOG(BLINKER_F("=========== Blinker Auto Control mode init! ==========="));
        BLINKER_LOG(BLINKER_F("Warning!EEPROM address 0-1279 is used for Auto Control!"));
        BLINKER_LOG(BLINKER_F("=========== DON'T USE THESE EEPROM ADDRESS! ==========="));
        BLINKER_LOG(BLINKER_F("======================================================="));

        BLINKER_LOG(BLINKER_F("Already used: "), BLINKER_ONE_AUTO_DATA_SIZE);

        _isAuto = true;
        // deserialization();
        // autoStart();
        autoInit();
    }
    
    bool BlinkerApi::autoTrigged(uint32_t _id)
    {
        BLINKER_LOG_ALL(BLINKER_F("autoTrigged id: "), _id);
        
        return BProto::autoPrint(_id);
    }

    bool BlinkerApi::checkCanOTA()
    {
        // #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined (BLINKER_AT_MQTT)
            #if defined(ESP8266)
                int boot_mode = (GPI >> 16) & 0xf;
                if (boot_mode == 1)
                {
                    // _setError(UPDATE_ERROR_BOOTSTRAP);
                    // return false;
                    BLINKER_ERR_LOG(BLINKER_F("==========================================================="));
                    BLINKER_ERR_LOG(BLINKER_F("Invalid bootstrapping state, reset ESP8266 before updating!"));
                    BLINKER_ERR_LOG(BLINKER_F("==========================================================="));
                
                    return false;
                }
            #endif
        // #endif        
                
        return true;
    }
    
    void BlinkerApi:: freshNTP()
    {
        if (_isNTPInit)
        {
            time_t now_ntp = ::time(nullptr);
            struct tm timeinfo;
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif
        }
    }

    
    bool BlinkerApi::ntpInit()
    {
        if (!_isNTPInit)
        {
            freshNTP();

            if ((millis() - _ntpStart) > BLINKER_NTP_TIMEOUT)
            {
                _ntpStart = millis();
            }
            else {
                return false;
            }

            ntpConfig();
            // String ntp1 = BLINKER_F("ntp1.aliyun.com");
            // String ntp2 = BLINKER_F("210.72.145.44");
            // String ntp3 = BLINKER_F("time.pool.aliyun.com");

            // configTime((long)(_timezone * 3600), 0, 
            //     ntp1.c_str(), ntp2.c_str(), ntp3.c_str());
            // configTime((long)(_timezone * 3600), 0, "ntp1.aliyun.com", "210.72.145.44", "time.pool.aliyun.com");

            time_t now_ntp = ::time(nullptr);

            float _com_timezone = abs(_timezone);
            if (_com_timezone < 1.0) _com_timezone = 1.0;

            if (now_ntp < _com_timezone * 3600 * 12)
            {
                ntpConfig();
                // configTime((long)(_timezone * 3600), 0, 
                //     ntp1.c_str(), ntp2.c_str(), ntp3.c_str());
                // configTime((long)(_timezone * 3600), 0, "ntp1.aliyun.com", "210.72.145.44", "time.pool.aliyun.com");
                now_ntp = ::time(nullptr);
                if (now_ntp < _com_timezone * 3600 * 12)
                {
                    ::delay(50);
                    now_ntp = ::time(nullptr);
                    return false;
                }
            }

            struct tm timeinfo;
            
            #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
            #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
            #endif

            BLINKER_LOG_ALL(BLINKER_F("Current time: "), asctime(&timeinfo));
            
            _isNTPInit = true;

            #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                loadTiming();
            #endif
        }

        return true;
    }

    
    void BlinkerApi::ntpConfig()
    {
        // String ntp1 = BLINKER_F("ntp1.aliyun.com");
        // String ntp2 = BLINKER_F("210.72.145.44");
        // String ntp3 = BLINKER_F("time.pool.aliyun.com");

        // configTime((long)(_timezone * 3600), 0, 
        //         ntp1.c_str(), ntp2.c_str(), ntp3.c_str());

        configTime((long)(_timezone * 3600), 0, "ntp1.aliyun.com", \
                    "210.72.145.44", "time.pool.aliyun.com");
    }

    
    void BlinkerApi::saveCountDown(uint32_t _data, char _action[])
    {
        EEPROM.begin(BLINKER_EEP_SIZE);
        EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, _data);
        EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _action);
        EEPROM.commit();
        EEPROM.end();
    }

    
    void BlinkerApi::saveLoop(uint32_t _data, char _action1[], char _action2[])
    {
        EEPROM.begin(BLINKER_EEP_SIZE);
        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, _data);
        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _action1);
        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _action2);
        EEPROM.commit();
        EEPROM.end();
    }

    
    void BlinkerApi::loadCountdown()
    {
        EEPROM.begin(BLINKER_EEP_SIZE);
        EEPROM.get(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, _cdData);
        EEPROM.get(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction);
        EEPROM.commit();
        EEPROM.end();

        _cdState    = _cdData >> 31;
        _cdRunState = _cdData >> 30 & 0x0001;
        _cdTime1    = _cdData >> 12 & 0x0FFF;
        _cdTime2    = _cdData       & 0x0FFF;

        if (_cdTime1 == 0)
        {
            _cdState = 0;
            _cdRunState = 0;
        }
        
        BLINKER_LOG_ALL(BLINKER_F("countdown state: "), _cdState ? "true" : "false");
        BLINKER_LOG_ALL(BLINKER_F("_cdRunState: "), _cdRunState);
        BLINKER_LOG_ALL(BLINKER_F("_totalTime: "), _cdTime1);
        BLINKER_LOG_ALL(BLINKER_F("_runTime: "), _cdTime2);
        BLINKER_LOG_ALL(BLINKER_F("_action: "), _cdAction);

        if (_cdState && _cdRunState)
        {
            uint32_t _cdTime1_;

            if (_cdTime1 * 60 > BLINKER_ONE_HOUR_TIME) _cdTime1_ = BLINKER_ONE_HOUR_TIME;
            else _cdTime1_ = _cdTime1 * 60;

            cdTicker.once(_cdTime1_, _cd_callback);

            _cdStart = millis();
            
            BLINKER_LOG_ALL(BLINKER_F("countdown start!"));
        }
    }

    
    void BlinkerApi::loadLoop()
    {
        EEPROM.begin(BLINKER_EEP_SIZE);
        EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP, _lpData);
        EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP_TRI, _lpTrigged_times);
        EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction1);
        EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction2);
        EEPROM.commit();
        EEPROM.end();

        _lpState    = _lpData >> 31;
        _lpRunState = _lpData >> 30 & 0x0001;
        _lpTimes    = _lpData >> 22 & 0x007F;
        _lpTime1    = _lpData >> 11 & 0x07FF;
        _lpTime2    = _lpData       & 0x07FF;
        
        BLINKER_LOG_ALL(BLINKER_F("loop state: "), _lpState ? "true" : "false");
        BLINKER_LOG_ALL(BLINKER_F("_lpRunState: "), _lpRunState);
        BLINKER_LOG_ALL(BLINKER_F("_times: "), _lpTimes);
        BLINKER_LOG_ALL(BLINKER_F("_tri_times: "), _lpTrigged_times);
        BLINKER_LOG_ALL(BLINKER_F("_time1: "), _lpTime1);
        BLINKER_LOG_ALL(BLINKER_F("_action1: "), _lpAction1);
        BLINKER_LOG_ALL(BLINKER_F("_time2: "), _lpTime2);
        BLINKER_LOG_ALL(BLINKER_F("_action2: "), _lpAction2);
        BLINKER_LOG_ALL(BLINKER_F("_lpData: "), _lpData);

        if (_lpState && _lpRunState && (_lpTimes == 0))
        {
            _lpRun1 = true;
            _lpStop = false;

            uint32_t _lpTime1_;

            if (_lpTime1 * 60 > BLINKER_ONE_HOUR_TIME) _lpTime1_ = BLINKER_ONE_HOUR_TIME;
            else _lpTime1_ = _lpTime1 * 60;

            _lpTime1_start = millis();
            lpTicker.once(_lpTime1_, _lp_callback);
            
            BLINKER_LOG_ALL(BLINKER_F("loop start!"));
        }
    }

    
    void BlinkerApi::loadTiming()
    {
        EEPROM.begin(BLINKER_EEP_SIZE);
        EEPROM.get(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, taskCount);
        uint32_t _tmData;
        char     _tmAction_[BLINKER_TIMER_TIMING_ACTION_SIZE];

        if (taskCount > BLINKER_TIMING_TIMER_SIZE)
        {
            taskCount = 0;
        }
        BLINKER_LOG_ALL(BLINKER_F("load timing taskCount: "), taskCount);

        for(uint8_t task = 0; task < taskCount; task++)
        {
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE 
                        , _tmData);
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE + 
                        BLINKER_TIMER_TIMING_SIZE, _tmAction_);

            timingTask[task] = new BlinkerTimingTimer(_tmData, STRING_format(_tmAction_));
            
            BLINKER_LOG_ALL(BLINKER_F("_tmData: "), _tmData);
            BLINKER_LOG_ALL(BLINKER_F("_tmAction: "), STRING_format(_tmAction_));
        }
        EEPROM.commit();
        EEPROM.end();

        uint8_t  wDay = wday();
        uint16_t nowMins = hour() * 60 + minute();

        freshTiming(wDay, nowMins);
    }

    
    void BlinkerApi::checkOverlapping(uint8_t checkDays, uint16_t checkMins)
    {
        for (uint8_t task = 0; task < taskCount; task++)
        {
            if((timingTask[task]->getTime() == checkMins) && \
                !timingTask[task]->isLoop() && \
                timingTask[task]->state() && \
                timingTask[task]->isTimingDay(checkDays))
            {

                timingTask[task]->disableTask();

                EEPROM.begin(BLINKER_EEP_SIZE);
                EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, taskCount);
                
                EEPROM.put( BLINKER_EEP_ADDR_TIMER_TIMING + \
                            task * BLINKER_ONE_TIMER_TIMING_SIZE, \
                            timingTask[task]->getTimerData());
            
                EEPROM.commit();
                EEPROM.end();
                
                BLINKER_LOG_ALL(BLINKER_F("disable timerData: "), timingTask[task]->getTimerData());
                BLINKER_LOG_ALL(BLINKER_F("disableTask: "), task);
            }
        }
    }

    
    void BlinkerApi::freshTiming(uint8_t wDay, uint16_t nowMins)
    {
        tmTicker.detach();

        uint8_t  cbackData;
        uint8_t  nextTask = BLINKER_TIMING_TIMER_SIZE;
        // uint16_t timingMinsNext;
        uint32_t apartSeconds = BLINKER_ONE_DAY_TIME;
        uint32_t checkSeconds = BLINKER_ONE_DAY_TIME;
        uint32_t nowSeconds = dtime();
        
        BLINKER_LOG_ALL(BLINKER_F("freshTiming wDay: "), wDay, 
                        BLINKER_F(", nowMins: "), nowMins, 
                        BLINKER_F(", nowSeconds: "), nowSeconds);

        for (uint8_t task = 0; task < taskCount; task++)
        {
            if (timingTask[task]->isTimingDay(wDay) && timingTask[task]->state())
            {
                if (timingTask[task]->getTime() > nowMins)
                {
                    checkSeconds = timingTask[task]->getTime() * 60 - nowSeconds;

                    // checkSeconds =  checkSeconds / 60 / 30;

                    if (checkSeconds <= apartSeconds) {
                        apartSeconds = checkSeconds;
                        nextTask = task;
                    }
                }
            }
            
            BLINKER_LOG_ALL(BLINKER_F("isTimingDay: "), timingTask[task]->isTimingDay(wDay));
            BLINKER_LOG_ALL(BLINKER_F("state: "), timingTask[task]->state());
            BLINKER_LOG_ALL(BLINKER_F("getTime: "), timingTask[task]->getTime());

            BLINKER_LOG_ALL(BLINKER_F("for nextTask: "), nextTask, 
                            BLINKER_F("  apartSeconds: "), apartSeconds, 
                            BLINKER_F(" wDay: "), wDay);
        }

        if (apartSeconds == BLINKER_ONE_DAY_TIME)
        {
            apartSeconds -= nowSeconds;

            // apartSeconds = apartSeconds / 60 / 30;
            BLINKER_LOG_ALL(BLINKER_F("nextTask: "), nextTask, 
                            BLINKER_F("  apartSeconds: "), apartSeconds, 
                            BLINKER_F(" wDay: "), wDay);
                            
            cbackData = nextTask;
        }
        else
        {
            BLINKER_LOG_ALL(BLINKER_F("nextTask: "), nextTask, 
                            BLINKER_F("  apartSeconds: "), apartSeconds, 
                            BLINKER_F(" wDay: "), wDay);
                            
            cbackData = nextTask;
        }
        BLINKER_LOG_ALL(BLINKER_F("cbackData: "), cbackData);

        if (apartSeconds > BLINKER_ONE_HOUR_TIME)
        {
            apartSeconds = BLINKER_ONE_HOUR_TIME;

            BLINKER_LOG_ALL(BLINKER_F("change apartSeconds: "), apartSeconds);
        }

        tmTicker.once(apartSeconds, timingHandle, cbackData);
    }

    
    void BlinkerApi::deleteTiming(uint8_t taskDel)
    {
        if (taskDel < taskCount)
        {
            // tmTicker.detach();

            for (uint8_t task = taskDel; task < (taskCount - 1); task++)
            {
                // timingTask[task]->freshTimer(timingTask[task + 1]->getTimerData(), 
                //     timingTask[task + 1]->getAction(), timingTask[task + 1]->getText());
                timingTask[task]->freshTimer(timingTask[task + 1]->getTimerData(), 
                                            timingTask[task + 1]->getAction());
            }

            delete timingTask[taskCount - 1];

            taskCount--;
            
            BLINKER_LOG_ALL(BLINKER_F("delete task: "), taskDel, BLINKER_F(" success!"));
            
            uint8_t  wDay = wday();
            uint16_t nowMins = hour() * 60 + minute();
            freshTiming(wDay, nowMins);
        }
        else
        {
            BLINKER_LOG_ALL(BLINKER_F("none task to delete!"));
        }
    }

    
    void BlinkerApi::addTimingTask(uint8_t taskSet, uint32_t timerData, const String & action)
    {
        BLINKER_LOG_ALL(BLINKER_F("addTimingTask taskSet: "), taskSet);
        BLINKER_LOG_ALL(BLINKER_F("addTimingTask timerData: "), timerData);
        
        if (taskSet <= taskCount && taskCount <= BLINKER_TIMING_TIMER_SIZE)
        {
            // tmTicker.detach();

            if (taskSet == taskCount)
            {
                if (taskCount == BLINKER_TIMING_TIMER_SIZE)
                {
                    BLINKER_ERR_LOG(BLINKER_F("timing timer task is full"));
                    return;
                }
                // timingTask[taskSet] = new BlinkerTimingTimer(timerData, action, text);
                timingTask[taskSet] = new BlinkerTimingTimer(timerData, action);
                taskCount++;
                
                BLINKER_LOG_ALL(BLINKER_F("new BlinkerTimingTimer"));
            }
            else
            {
                // timingTask[taskSet]->freshTimer(timerData, action, text);
                timingTask[taskSet]->freshTimer(timerData, action);

                BLINKER_LOG_ALL(BLINKER_F("freshTimer"));
            }

            // if (taskSet <= taskCount) taskCount++;
            
            BLINKER_LOG_ALL(BLINKER_F("taskCount: "), taskCount);
            
            uint8_t  wDay = wday();
            uint16_t nowMins = hour() * 60 + minute();

            freshTiming(wDay, nowMins);
        }
        else {
            BLINKER_ERR_LOG(BLINKER_F("timing timer task is full"));
        }
    }

    
    void BlinkerApi::checkTimerErase()
    {
        // #if defined(ESP8266)
        static uint8_t isErase;
        // #endif

        EEPROM.begin(BLINKER_EEP_SIZE);
        EEPROM.get(BLINKER_EEP_ADDR_TIMER_ERASE, isErase);

        if (isErase)
        {
            for (uint16_t _addr = BLINKER_EEP_ADDR_TIMER;
                _addr < BLINKER_EEP_ADDR_TIMER_END; _addr++)
            {
                EEPROM.put(_addr, "\0");
            }
        }

        EEPROM.commit();
        EEPROM.end();
    }

    
    String BlinkerApi::timerSetting()
    {

        String _data = BLINKER_F("\"");
        _data += BLINKER_F(BLINKER_CMD_COUNTDOWN);
        _data += BLINKER_F("\":");
        _data += STRING_format(_cdState ? "true" : "false");
        _data += BLINKER_F(",\"");
        _data += BLINKER_F(BLINKER_CMD_LOOP);
        _data += BLINKER_F("\":");
        _data += STRING_format(_lpState ? "true" : "false");
        _data += BLINKER_F(",\"");
        _data += BLINKER_F(BLINKER_CMD_TIMING);
        _data += BLINKER_F("\":");
        _data += STRING_format(taskCount ? "true" : "false");


        BLINKER_LOG_ALL(BLINKER_F("timerSetting: "), _data);

        return _data;
    }

    
    String BlinkerApi::countdownConfig()
    {
        String cdData;

        if (!_cdState)
        {
            cdData = BLINKER_F("{\"");
            cdData += BLINKER_F(BLINKER_CMD_COUNTDOWN);
            cdData += BLINKER_F("\":false}");
        }
        else
        {
            if (_cdRunState)
            {
                cdData = BLINKER_F("{\"");
                cdData += BLINKER_F(BLINKER_CMD_COUNTDOWN);
                cdData += BLINKER_F("\":{\"");
                cdData += BLINKER_F(BLINKER_CMD_RUN);
                cdData += BLINKER_F("\":");
                cdData += STRING_format(_cdRunState ? 1 : 0);
                cdData += BLINKER_F(",\"");
                cdData += BLINKER_F(BLINKER_CMD_TOTALTIME);
                cdData += BLINKER_F("\":");
                cdData += STRING_format(_cdTime1);
                cdData += BLINKER_F(",\"");
                cdData += BLINKER_F(BLINKER_CMD_RUNTIME);
                cdData += BLINKER_F("\":");
                cdData += STRING_format((millis() - _cdStart) / 1000 / 60);
                cdData += BLINKER_F(",\"");
                cdData += BLINKER_F(BLINKER_CMD_ACTION);
                cdData += BLINKER_F("\":");
                cdData += _cdAction;
                cdData += BLINKER_F("}}");
            }
            else
            {
                cdData = BLINKER_F("{\"");
                cdData += BLINKER_F(BLINKER_CMD_COUNTDOWN);
                cdData += BLINKER_F("\":{\"");
                cdData += BLINKER_F(BLINKER_CMD_RUN);
                cdData += BLINKER_F("\":");
                cdData += STRING_format(_cdRunState ? 1 : 0);
                cdData += BLINKER_F(",\"");
                cdData += BLINKER_F(BLINKER_CMD_TOTALTIME);
                cdData += BLINKER_F("\":");
                cdData += STRING_format(_cdTime1);
                cdData += BLINKER_F(",\"");
                cdData += BLINKER_F(BLINKER_CMD_RUNTIME);
                cdData += BLINKER_F("\":");
                cdData += STRING_format(_cdTime2);
                cdData += BLINKER_F(",\"");
                cdData += BLINKER_F(BLINKER_CMD_ACTION);
                cdData += BLINKER_F("\":");
                cdData += _cdAction;
                cdData += BLINKER_F("}}");
            }
        }

        return cdData;
    }

    
    String BlinkerApi::timingConfig()
    {
        String timingTaskStr = BLINKER_F("{\"");
        timingTaskStr += BLINKER_F(BLINKER_CMD_TIMING);
        timingTaskStr += BLINKER_F("\":[");

        for (uint8_t task = 0; task < taskCount; task++)
        {
            //Serial.print(timingTask[task].getTimingCfg());
            timingTaskStr += getTimingCfg(task);
            if (task + 1 < taskCount)
            {
                //Serial.println(",");
                timingTaskStr += BLINKER_F(",");
            }
            // else {
            //     Serial.println("");
            // }
        }
        timingTaskStr += BLINKER_F("]}");
        
        BLINKER_LOG_ALL(BLINKER_F("timingTaskStr: "), timingTaskStr);
        
        return timingTaskStr;
    }

    
    String BlinkerApi::getTimingCfg(uint8_t task)
    {
        String timingDayStr = BLINKER_F("");
        uint8_t timingDay = timingTask[task]->getTimingday();
        if (timingTask[task]->isLoop())
        {
            for (uint8_t day = 0; day < 7; day++)
            {
                // timingDayStr += (timingDay & (uint8_t)pow(2,day)) ? String(day):String("");
                if ((timingDay >> day) & 0x01) {
                    timingDayStr += STRING_format(1);
                    // if (day < 6 && (timingDay >> (day + 1)))
                    //     timingDayStr += STRING_format(",");
                }
                else {
                    timingDayStr += STRING_format(0);
                }
                // timingDayStr += String((day < 6) ? ((timingDay >> (day + 1)) ? ",":""):"");
            }

            BLINKER_LOG_ALL(BLINKER_F("timingDayStr: "), timingDayStr);

        }
        else {
            timingDayStr = BLINKER_F("0000000");

            BLINKER_LOG_ALL(BLINKER_F("timingDayStr: "), timingDay);
        }

        String timingConfig = BLINKER_F("{\"");
        timingConfig += BLINKER_F(BLINKER_CMD_TASK);
        timingConfig += BLINKER_F("\":");
        timingConfig += STRING_format(task);
        timingConfig += BLINKER_F(",\"");
        timingConfig += BLINKER_F(BLINKER_CMD_ENABLE);
        timingConfig += BLINKER_F("\":");
        timingConfig += STRING_format((timingTask[task]->state()) ? 1 : 0);
        timingConfig += BLINKER_F(",\"");
        timingConfig += BLINKER_F(BLINKER_CMD_DAY);
        timingConfig += BLINKER_F("\":\"");
        timingConfig += timingDayStr;
        timingConfig += BLINKER_F("\",\"");
        timingConfig += BLINKER_F(BLINKER_CMD_TIME);
        timingConfig += BLINKER_F("\":");
        timingConfig += STRING_format(timingTask[task]->getTime());
        timingConfig += BLINKER_F(",\"");
        timingConfig += BLINKER_F(BLINKER_CMD_ACTION);
        timingConfig += BLINKER_F("\":");
        timingConfig += timingTask[task]->getAction();
        timingConfig += BLINKER_F("}");

        return timingConfig;
    }

    
    String BlinkerApi::loopConfig()
    {
        String lpData;
        if (!_lpState) {
            lpData = BLINKER_F("{\"");
            lpData += BLINKER_F(BLINKER_CMD_LOOP);
            lpData += BLINKER_F("\":false}");
        }
        else {
            lpData = BLINKER_F("{\"");
            lpData += BLINKER_F(BLINKER_CMD_LOOP);
            lpData += BLINKER_F("\":{\"");
            lpData += BLINKER_F(BLINKER_CMD_TIMES);
            lpData += BLINKER_F("\":");
            lpData += STRING_format(_lpTimes);
            lpData += BLINKER_F(",\"");
            lpData += BLINKER_F(BLINKER_CMD_RUN);
            lpData += BLINKER_F("\":");
            lpData += STRING_format(_lpRunState ? 1 : 0);
            lpData += BLINKER_F(",\"");
            lpData += BLINKER_F(BLINKER_CMD_TRIGGED);
            lpData += BLINKER_F("\":");
            lpData += STRING_format(_lpTimes ? _lpTrigged_times : 0);
            lpData += BLINKER_F(",\"");
            lpData += BLINKER_F(BLINKER_CMD_TIME1);
            lpData += BLINKER_F("\":");
            lpData += STRING_format(_lpTime1);
            lpData += BLINKER_F(",\"");
            lpData += BLINKER_F(BLINKER_CMD_ACTION1);
            lpData += BLINKER_F("\":");
            lpData += _lpAction1;
            lpData += BLINKER_F(",\"");
            lpData += BLINKER_F(BLINKER_CMD_TIME2);
            lpData += BLINKER_F("\":");
            lpData += STRING_format(_lpTime2);
            lpData += BLINKER_F(",\"");
            lpData += BLINKER_F(BLINKER_CMD_ACTION2);
            lpData += BLINKER_F("\":");
            lpData += _lpAction2;
            lpData += BLINKER_F("}}");
        }

        return lpData;
    }

    
    bool BlinkerApi::timerManager(const JsonObject& data, bool _noSet)
    {
        bool isSet = false;
        bool isCount = false;
        bool isLoop = false;
        bool isTiming = false;

        if (!_noSet)
        {
            isSet = STRING_contains_string(BProto::dataParse(), BLINKER_CMD_SET);
            isCount = STRING_contains_string(BProto::dataParse(), BLINKER_CMD_COUNTDOWN);
            isLoop = STRING_contains_string(BProto::dataParse(), BLINKER_CMD_LOOP);
            isTiming = STRING_contains_string(BProto::dataParse(), BLINKER_CMD_TIMING);
        }
        else {
            isCount = data.containsKey(BLINKER_CMD_COUNTDOWN);
            isLoop = data.containsKey(BLINKER_CMD_LOOP);
            isTiming = data.containsKey(BLINKER_CMD_TIMING);
        }

        if ((isSet || _noSet) && (isCount || isLoop || isTiming))
        {
            _fresh = true;
            
            BLINKER_LOG_ALL(BLINKER_F("get timer setting"));

            if (isCount)
            {

                String _delete = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN];

                if (_delete == "dlt") _cdState = false;
                else _cdState = true;

                if (_cdState)
                {
                    if (isSet)
                    {
                        _cdRunState = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_RUN];
                    }
                    else if(_noSet)
                    {
                        _cdRunState = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_RUN];
                    }
                    
                    BLINKER_LOG_ALL(BLINKER_F("countdown state: "), _cdState ? "true" : "false");

                    if (isSet)
                    {
                        // _cdRunState = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_STATE];
                        // _cdRunState = _cdState;
                        int32_t _totalTime = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_TOTALTIME];
                        // _totalTime = 60 * _totalTime;
                        int32_t _runTime = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_RUNTIME];
                        // _runTime = 60 * _runTime;
                        String _action = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_ACTION];

                        if (_action.length() > BLINKER_TIMER_COUNTDOWN_ACTION_SIZE)
                        {
                            BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                            return true;
                        }

                        if (_cdRunState && _action.length())
                        {
                            // _cdAction = _action;
                            strcpy(_cdAction, _action.c_str());
                            _cdTime1 = _totalTime;
                            _cdTime2 = _runTime;
                        }

                        if (!_cdRunState && _action.length() == 0)
                        {
                            _cdTime2 += (millis() - _cdStart) / 1000 / 60;
                        }
                        // else if (_cdRunState && _action.length() == 0) {
                        //     _cdTime2 = 0;
                        // }
                        
                        BLINKER_LOG_ALL(BLINKER_F("_cdRunState: "), _cdRunState);
                    }
                    else if (_noSet)
                    {
                        // _cdRunState = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_STATE];
                        // _cdRunState = _cdState;
                        int32_t _totalTime = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_TOTALTIME];
                        // _totalTime = 60 * _totalTime;
                        int32_t _runTime = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_RUNTIME];
                        // _runTime = 60 * _runTime;
                        String _action = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_ACTION];

                        if (_action.length() > BLINKER_TIMER_COUNTDOWN_ACTION_SIZE)
                        {
                            BLINKER_ERR_LOG("TIMER ACTION TOO LONG");
                            return true;
                        }

                        if (_cdRunState && _action.length())
                        {
                            // _cdAction = _action;
                            strcpy(_cdAction, _action.c_str());
                            _cdTime1 = _totalTime;
                            _cdTime2 = _runTime;
                        }

                        if (!_cdRunState && _action.length() == 0)
                        {
                            _cdTime2 += (millis() - _cdStart) / 1000 / 60;
                        }
                        // else if (_cdRunState && _action.length() == 0) {
                        //     _cdTime2 = 0;
                        // }
                        
                        BLINKER_LOG_ALL(BLINKER_F("_cdRunState: "), _cdRunState);
                    }
                    _cdData = _cdState << 31 | _cdRunState << 30 | _cdTime1 << 12 | _cdTime2;

                    BLINKER_LOG_ALL(BLINKER_F("_totalTime: "), _cdTime1);
                    BLINKER_LOG_ALL(BLINKER_F("_runTime: "), _cdTime2);
                    BLINKER_LOG_ALL(BLINKER_F("_action: "), _cdAction);
                    BLINKER_LOG_ALL(BLINKER_F("_cdData: "), _cdData);

                    // char _cdAction_[BLINKER_TIMER_COUNTDOWN_ACTION_SIZE];
                    // strcpy(_cdAction_, _cdAction.c_str());

                    EEPROM.begin(BLINKER_EEP_SIZE);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, _cdData);
                    // EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction_);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction);
                    EEPROM.commit();
                    EEPROM.end();

                    if (_cdState && _cdRunState)
                    {
                        // _cdTime1 = _cdTime1 - _cdTime2;
                        // _cdTime2 = 0;

                        uint32_t _cdTime1_ = _cdTime1 - _cdTime2;

                        if (_cdTime1_ * 60 > BLINKER_ONE_HOUR_TIME) _cdTime1_ = BLINKER_ONE_HOUR_TIME;
                        else _cdTime1_ = _cdTime1_ * 60;

                        cdTicker.once(_cdTime1_, _cd_callback);

                        _cdStart = millis();
                        
                        BLINKER_LOG_ALL(BLINKER_F("countdown start! time: "), _cdTime1);
                    }
                    else
                    {
                        cdTicker.detach();
                    }
                }
                else {
                    _cdRunState = 0;
                    _cdTime1 = 0;
                    _cdTime2 = 0;
                    // _cdAction = "";
                    // memcpy(_cdAction, '\0', BLINKER_ACTION_SIZE);

                    _cdData = _cdState << 15 | _cdRunState << 14 | (_cdTime1 - _cdTime2);

                    BLINKER_LOG_ALL(BLINKER_F("countdown state: "), _cdState ? "true" : "false");
                    BLINKER_LOG_ALL(BLINKER_F("_cdRunState: "), _cdRunState);
                    BLINKER_LOG_ALL(BLINKER_F("_totalTime: "), _cdTime1);
                    BLINKER_LOG_ALL(BLINKER_F("_runTime: "), _cdTime2);
                    BLINKER_LOG_ALL(BLINKER_F("_action: "), _cdAction);
                    BLINKER_LOG_ALL(BLINKER_F("_cdData: "), _cdData);

                    // char _cdAction_[BLINKER_TIMER_COUNTDOWN_ACTION_SIZE];
                    // strcpy(_cdAction_, _cdAction.c_str());

                    EEPROM.begin(BLINKER_EEP_SIZE);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, _cdData);
                    // EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction_);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction);
                    EEPROM.commit();
                    EEPROM.end();

                    cdTicker.detach();
                }

                // static_cast<Proto*>(this)->checkState(false);
                BProto::_timerPrint(countdownConfig());            
                BProto::printNow();
                return true;
            }
            else if (isLoop)
            {
                _lpState = true;

                String _delete = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP];

                if (_delete == "dlt") _lpState = false;
                else _lpState = true;

                if (_lpState)
                {
                    if (isSet)
                    {
                        _lpRunState = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_RUN];
                    }
                    else if (_noSet)
                    {
                        _lpRunState = data[BLINKER_CMD_LOOP][BLINKER_CMD_RUN];
                    }
                    
                    BLINKER_LOG_ALL(BLINKER_F("loop state: "), _lpState ? "true" : "false");
                    
                    if (isSet)
                    {
                        int8_t _times = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TIMES];
                        int8_t _tri_times = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TRIGGED];
                        // _lpRunState = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_STATE];
                        // _lpRunState = _lpState;
                        int32_t _time1 = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TIME1];
                        // _time1 = 60 * _time1;
                        String _action1 = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_ACTION1];
                        int32_t _time2 = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TIME2];
                        // _time2 = 60 * _time2;
                        String _action2 = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_ACTION2];

                        if (_action1.length() > BLINKER_TIMER_LOOP_ACTION1_SIZE)
                        {
                            BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                            return true;
                        }

                        if (_action2.length() > BLINKER_TIMER_LOOP_ACTION2_SIZE)
                        {
                            BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                            return true;
                        }

                        if (_lpRunState && _action2.length())
                        {
                            // _lpAction1 = _action1;
                            // _lpAction2 = _action2;
                            strcpy(_lpAction1, _action1.c_str());
                            strcpy(_lpAction2, _action2.c_str());

                            _lpTimes = _times;
                            _lpTrigged_times = _tri_times;
                            _lpTime1 = _time1;
                            _lpTime2 = _time2;
                        }
                        
                        BLINKER_LOG_ALL(BLINKER_F("_lpRunState: "), _lpRunState);
                        
                    }
                    else if (_noSet)
                    {
                        int8_t _times = data[BLINKER_CMD_LOOP][BLINKER_CMD_TIMES];
                        int8_t _tri_times = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TRIGGED];
                        // _lpRunState = data[BLINKER_CMD_LOOP][BLINKER_CMD_STATE];
                        // _lpRunState = _lpState;
                        int32_t _time1 = data[BLINKER_CMD_LOOP][BLINKER_CMD_TIME1];
                        // _time1 = 60 * _time1;
                        String _action1 = data[BLINKER_CMD_LOOP][BLINKER_CMD_ACTION1];
                        int32_t _time2 = data[BLINKER_CMD_LOOP][BLINKER_CMD_TIME2];
                        // _time2 = 60 * _time2;
                        String _action2 = data[BLINKER_CMD_LOOP][BLINKER_CMD_ACTION2];

                        if (_action1.length() > BLINKER_TIMER_LOOP_ACTION1_SIZE)
                        {
                            BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                            return true;
                        }

                        if (_action2.length() > BLINKER_TIMER_LOOP_ACTION2_SIZE)
                        {
                            BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                            return true;
                        }

                        if (_lpRunState && _action2.length()) {
                            // _lpAction1 = _action1;
                            // _lpAction2 = _action2;
                            strcpy(_lpAction1, _action1.c_str());
                            strcpy(_lpAction2, _action2.c_str());

                            _lpTimes = _times;
                            _lpTrigged_times = _tri_times;
                            _lpTime1 = _time1;
                            _lpTime2 = _time2;
                        }
                        
                        BLINKER_LOG_ALL(BLINKER_F("_lpRunState: "), _lpRunState);
                    }

                    if (_lpTimes > 100) _lpTimes = 0;

                    _lpData = _lpState << 31 | _lpRunState << 30 | _lpTimes << 22 | _lpTime1 << 11 | _lpTime2;

                    BLINKER_LOG_ALL(BLINKER_F("_times: "), _lpTimes);
                    BLINKER_LOG_ALL(BLINKER_F("_tri_times: "), _lpTrigged_times);
                    BLINKER_LOG_ALL(BLINKER_F("_time1: "), _lpTime1);
                    BLINKER_LOG_ALL(BLINKER_F("_action1: "), _lpAction1);
                    BLINKER_LOG_ALL(BLINKER_F("_time2: "), _lpTime2);
                    BLINKER_LOG_ALL(BLINKER_F("_action2: "), _lpAction2);
                    BLINKER_LOG_ALL(BLINKER_F("_lpData: "), _lpData);

                    // char _lpAction_1[BLINKER_TIMER_LOOP_ACTION1_SIZE];
                    // char _lpAction_2[BLINKER_TIMER_LOOP_ACTION2_SIZE];
                    // strcpy(_lpAction_1, _lpAction1.c_str());
                    // strcpy(_lpAction_2, _lpAction2.c_str());

                    EEPROM.begin(BLINKER_EEP_SIZE);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, _lpData);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_TRI, _lpTrigged_times);
                    // EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction_1);
                    // EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction_2);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction1);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction2);
                    EEPROM.commit();
                    EEPROM.end();

                    if (_lpState && _lpRunState)
                    {
                        _lpRun1 = true;
                        // _lpTrigged_times = 0;
                        _lpStop = false;

                        uint32_t _lpTime1_;

                        if (_lpTime1 * 60 > BLINKER_ONE_HOUR_TIME) _lpTime1_ = BLINKER_ONE_HOUR_TIME;
                        else _lpTime1_ = _lpTime1 * 60;

                        _lpTime1_start = millis();
                        lpTicker.once(_lpTime1_, _lp_callback);

                        BLINKER_LOG_ALL(BLINKER_F("loop start!"));
                    }
                    else
                    {
                        lpTicker.detach();
                    }
                }
                else
                {
                    _lpRunState = 0;
                    _lpTimes = 0;
                    _lpTrigged_times = 0;
                    _lpTime1 = 0;
                    _lpTime2 = 0;
                    // _lpAction1 = "";
                    // _lpAction2 = "";
                    // memcpy(_lpAction1, '\0', BLINKER_ACTION_SIZE);
                    // memcpy(_lpAction2, '\0', BLINKER_ACTION_SIZE);

                    _lpData = _lpState << 31 | _lpRunState << 30 | _lpTimes << 22 | _lpTime1 << 11 | _lpTime2;

                    BLINKER_LOG_ALL(BLINKER_F("loop state: "), _lpState ? "true" : "false");
                    BLINKER_LOG_ALL(BLINKER_F("_lpRunState: "), _lpRunState);
                    BLINKER_LOG_ALL(BLINKER_F("_times: "), _lpTimes);
                    BLINKER_LOG_ALL(BLINKER_F("_tri_times: "), _lpTrigged_times);
                    BLINKER_LOG_ALL(BLINKER_F("_time1: "), _lpTime1);
                    BLINKER_LOG_ALL(BLINKER_F("_action1: "), _lpAction1);
                    BLINKER_LOG_ALL(BLINKER_F("_time2: "), _lpTime2);
                    BLINKER_LOG_ALL(BLINKER_F("_action2: "), _lpAction2);
                    BLINKER_LOG_ALL(BLINKER_F("_lpData: "), _lpData);

                    // char _lpAction_1[BLINKER_TIMER_LOOP_ACTION1_SIZE];
                    // char _lpAction_2[BLINKER_TIMER_LOOP_ACTION2_SIZE];
                    // strcpy(_lpAction_1, _lpAction1.c_str());
                    // strcpy(_lpAction_2, _lpAction2.c_str());

                    EEPROM.begin(BLINKER_EEP_SIZE);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, _lpData);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_TRI, _lpTrigged_times);
                    // EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction_1);
                    // EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction_2);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction1);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction2);
                    EEPROM.commit();
                    EEPROM.end();

                    lpTicker.detach();
                }
                
                BProto::_timerPrint(loopConfig());
                BProto::printNow();
                return true;
            }
            else if (isTiming)
            {
                bool isDelet = STRING_contains_string(BProto::dataParse(), BLINKER_CMD_DELETETASK);

                _tmState = true;
                
                if (isSet)
                {
                    _tmRunState = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_ENABLE];
                }
                else if (_noSet)
                {
                    _tmRunState = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_ENABLE];
                }
                
                BLINKER_LOG_ALL(BLINKER_F("timing state: "), _tmState ? "true" : "false");

                int32_t _time;
                String _action;
                String _text;
                uint8_t _task;

                if (isSet && !isDelet)
                {
                    // _tmRunState = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_STATE];
                    // _tmRunState = _tmState;
                    _time = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_TIME];
                    // _time = 60 * _time;
                    String tm_action = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_ACTION];
                    // String tm_text = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_TEXT];
                    _task = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_TASK];

                    // _tmAction = _action;

                    if (tm_action.length() > BLINKER_TIMER_TIMING_ACTION_SIZE)
                    {
                        BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                        return true;
                    }

                    _action = tm_action;
                    // _text = tm_text;

                    // _tmTime = _time;

                    String tm_day = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY];

                    _timingDay = 0;

                    if (tm_day.toInt() == 0)
                    {
                        if (60 * _time > dtime())
                        {
                            _timingDay |= (0x01 << wday());//timeinfo.tm_wday(uint8_t)pow(2,timeinfo.tm_wday);
                        }
                        else {
                            _timingDay |= (0x01 << ((wday() + 1) % 7));//timeinfo.tm_wday(uint8_t)pow(2,(timeinfo.tm_wday + 1) % 7);
                        }

                        _isTimingLoop = false;
                        
                        BLINKER_LOG_ALL(BLINKER_F("timingDay: "), _timingDay);
                    }
                    else
                    {

                        _isTimingLoop = true;

                        // uint8_t taskDay;

                        for (uint8_t day = 0; day < 7; day++)
                        {
                            if (tm_day.substring(day, day+1) == "1")
                            {
                                _timingDay |= (0x01 << day);

                                BLINKER_LOG_ALL(BLINKER_F("day: "), day, BLINKER_F(" timingDay: "), _timingDay);
                            }
                        }
                    }

    //                     if (data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][0] == 7) {
    //                         if (_tmTime2 > dtime()) {
    //                             _timingDay |= (0x01 << wday());//timeinfo.tm_wday(uint8_t)pow(2,timeinfo.tm_wday);
    //                         }
    //                         else {
    //                             _timingDay |= (0x01 << ((wday() + 1) % 7));//timeinfo.tm_wday(uint8_t)pow(2,(timeinfo.tm_wday + 1) % 7);
    //                         }

    //                         _isTimingLoop = false;
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("timingDay: "), _timingDay);
    // #endif
    //                     }
    //                     else {
    //                         uint8_t taskDay = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][0];
    //                         _timingDay |= (0x01 << taskDay);//(uint8_t)pow(2,taskDay);
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("day: "), taskDay, BLINKER_F(" timingDay: "), _timingDay);
    // #endif

    //                         for (uint8_t day = 1;day < 7;day++) {
    //                             taskDay = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][day];
    //                             if (taskDay > 0) {
    //                                 _timingDay |= (0x01 << taskDay);//(uint8_t)pow(2,taskDay);
    // #ifdef BLINKER_DEBUG_ALL
    //                                 BLINKER_LOG(BLINKER_F("day: "), taskDay, BLINKER_F(" timingDay: "), _timingDay);
    // #endif
    //                             }
    //                         }

    //                         _isTimingLoop = true;
    //                     }

                    BLINKER_LOG_ALL(BLINKER_F("timingDay: "), _timingDay);
                    // BLINKER_LOG_ALL(BLINKER_F("_text: "), _text);
                    BLINKER_LOG_ALL(BLINKER_F("_tmRunState: "), _tmRunState);
                    BLINKER_LOG_ALL(BLINKER_F("_isTimingLoop: "), _isTimingLoop ? "true":"false");
                    BLINKER_LOG_ALL(BLINKER_F("_time: "), _time);
                    BLINKER_LOG_ALL(BLINKER_F("_action: "), _action);

                    uint32_t _timerData = _isTimingLoop << 31 | _tmRunState << 23 | _timingDay << 11 | _time;

                    // addTimingTask(_task, _timerData, _action, _text);
                    addTimingTask(_task, _timerData, _action);
                }
                else if (_noSet)
                {
                    // _tmRunState = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_STATE];
                    // _tmRunState = _tmState;
                    _time = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_TIME];
                    // _time = 60 * _time;
                    String tm_action = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_ACTION];
                    // String tm_text = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_TEXT];
                    _task = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_TASK];

                    // _tmAction = _action;

                    if (tm_action.length() > BLINKER_TIMER_TIMING_ACTION_SIZE)
                    {
                        BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                        return true;
                    }

                    _action = tm_action;
                    // _text = tm_text;

                    // _tmTime = _time;

                    String tm_day = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY];

                    if (tm_day.toInt() == 0)
                    {
                        if (60 * _time > dtime())
                        {
                            _timingDay |= (0x01 << wday());//timeinfo.tm_wday(uint8_t)pow(2,timeinfo.tm_wday);
                        }
                        else {
                            _timingDay |= (0x01 << ((wday() + 1) % 7));//timeinfo.tm_wday(uint8_t)pow(2,(timeinfo.tm_wday + 1) % 7);
                        }

                        _isTimingLoop = false;
                        
                        BLINKER_LOG_ALL(BLINKER_F("timingDay: "), _timingDay);
                    }
                    else
                    {
                        // uint8_t taskDay;

                        _isTimingLoop = true;

                        for (uint8_t day = 0; day < 7; day++)
                        {
                            if (tm_day.substring(day, day+1) == "1")
                            {
                                _timingDay |= (0x01 << day);

                                BLINKER_LOG_ALL(BLINKER_F("day: "), day, BLINKER_F(" timingDay: "), _timingDay);
                            }
                        }
                    }

    //                     if (data[BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][0] == 7) {
    //                         if (_tmTime2 > dtime()) {
    //                             _timingDay |= (0x01 << wday());//timeinfo.tm_wday(uint8_t)pow(2,timeinfo.tm_wday);
    //                         }
    //                         else {
    //                             _timingDay |= (0x01 << ((wday() + 1) % 7));//timeinfo.tm_wday(uint8_t)pow(2,(timeinfo.tm_wday + 1) % 7);
    //                         }

    //                         _isTimingLoop = false;
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("timingDay: "), _timingDay);
    // #endif
    //                     }
    //                     else {
    //                         uint8_t taskDay = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][0];
    //                         _timingDay |= (0x01 << taskDay);//(uint8_t)pow(2,taskDay);
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("day: "), taskDay, BLINKER_F(" timingDay: "), _timingDay);
    // #endif

    //                         for (uint8_t day = 1;day < 7;day++) {
    //                             taskDay = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][day];
    //                             if (taskDay > 0) {
    //                                 _timingDay |= (0x01 << taskDay);//(uint8_t)pow(2,taskDay);
    // #ifdef BLINKER_DEBUG_ALL
    //                                 BLINKER_LOG(BLINKER_F("day: "), taskDay, BLINKER_F(" timingDay: "), _timingDay);
    // #endif
    //                             }
    //                         }

    //                         _isTimingLoop = true;
    //                     }

                    BLINKER_LOG_ALL(BLINKER_F("timingDay: "), _timingDay);
                    // BLINKER_LOG_ALL(BLINKER_F("_text: "), _text);
                    BLINKER_LOG_ALL(BLINKER_F("_tmRunState: "), _tmRunState);
                    BLINKER_LOG_ALL(BLINKER_F("_isTimingLoop: "), _isTimingLoop ? "true":"false");
                    BLINKER_LOG_ALL(BLINKER_F("_time: "), _time);
                    BLINKER_LOG_ALL(BLINKER_F("_action: "), _action);
                    
                    uint32_t _timerData = _isTimingLoop << 31 | _tmRunState << 23 | _timingDay << 11 | _time;

                    // addTimingTask(_task, _timerData, _action, _text);
                    addTimingTask(_task, _timerData, _action);
                }
                else if (isDelet)
                {
                    uint8_t _delTask = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DELETETASK];

                    deleteTiming(_delTask);
                }

                char _tmAction_[BLINKER_TIMER_TIMING_ACTION_SIZE];
                
                EEPROM.begin(BLINKER_EEP_SIZE);
                EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, taskCount);
                for(uint8_t task = 0; task < taskCount; task++)
                {
                    strcpy(_tmAction_, timingTask[task]->getAction());

                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE
                                , timingTask[task]->getTimerData());
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE + 
                                BLINKER_TIMER_TIMING_SIZE, _tmAction_);
                                
                    BLINKER_LOG_ALL(BLINKER_F("getTimerData: "), timingTask[task]->getTimerData());
                    BLINKER_LOG_ALL(BLINKER_F("_tmAction_: "), _tmAction_);
                }
                EEPROM.commit();
                EEPROM.end();

                BProto::_timerPrint(timingConfig());
                BProto::printNow();

                BLINKER_LOG_FreeHeap_ALL();

                return true;
            }
        }
        else if (data.containsKey(BLINKER_CMD_GET))
        {
            String get_timer = data[BLINKER_CMD_GET];

            if (get_timer == BLINKER_CMD_TIMER)
            {
                BProto::_timerPrint(timerSetting());
                BProto::printNow();
                _fresh = true;
                return true;
            }
            else if (get_timer == BLINKER_CMD_COUNTDOWN)
            {
                BProto::_timerPrint(countdownConfig());
                BProto::printNow();
                _fresh = true;
                return true;
            }
            else if (get_timer == BLINKER_CMD_LOOP)
            {
                BProto::_timerPrint(loopConfig());
                BProto::printNow();
                _fresh = true;
                return true;
            }
            else if (get_timer == BLINKER_CMD_TIMING)
            {
                BProto::_timerPrint(timingConfig());
                BProto::printNow();
                _fresh = true;
                return true;
            }
        }
        else
        {
            return false;
        }

        return false;
    }

    
    bool BlinkerApi::checkTimer()
    {
        if (_cdTrigged)
        {
            _cdTrigged = false;

            // _cdRunState = false;
            _cdState = false;
            // _cdData |= _cdRunState << 14;
            // _cdData = _cdState << 15 | _cdRunState << 14 | (_cdTime1 - _cdTime2);
            _cdData = _cdState << 31 | _cdRunState << 30 | _cdTime1 << 12 | _cdTime2;
            saveCountDown(_cdData, _cdAction);
            
            BLINKER_LOG_ALL(BLINKER_F("countdown trigged, action is: "), _cdAction);
            
            // _parse(_cdAction);

            #if defined(BLINKER_AT_MQTT)
                BProto::serialPrint(_cdAction);
            #else
                parse(_cdAction, true);
            #endif
        }
        if (_lpTrigged)
        {
            _lpTrigged = false;

            if (_lpStop)
            {
                // _lpRunState = false;
                _lpState = false;
                // _lpData |= _lpRunState << 30;
                _lpData = _lpState << 31 | _lpRunState << 30 | _lpTimes << 22 | _lpTime1 << 11 | _lpTime2;
                saveLoop(_lpData, _lpAction1, _lpAction2);
            }

            if (_lpRun1)
            {
                BLINKER_LOG_ALL(BLINKER_F("loop trigged, action is: "), _lpAction2);
                // _parse(_lpAction2);

                #if defined(BLINKER_AT_MQTT)
                    BProto::serialPrint(_lpAction2);
                #else
                    parse(_lpAction2, true);
                #endif
            }
            else
            {
                
                BLINKER_LOG_ALL(BLINKER_F("loop trigged, action is: "), _lpAction1);
                // _parse(_lpAction1);

                #if defined(BLINKER_AT_MQTT)
                    BProto::serialPrint(_lpAction1);
                #else
                    parse(_lpAction1, true);
                #endif
            }
        }
        if (_tmTrigged)
        {
            _tmTrigged = false;

    //             if (_tmRun1) {
    // #ifdef BLINKER_DEBUG_ALL
    //                 BLINKER_LOG(BLINKER_F("timing trigged, action is: "), _tmAction2);
    // #endif
    //                 // _parse(_tmAction2);
    //                 parse(_tmAction2, true);
    //             }
    //             else {
    // #ifdef BLINKER_DEBUG_ALL
    //                 BLINKER_LOG(BLINKER_F("timing trigged, action is: "), _tmAction1);
    // #endif
    //                 // _parse(_tmAction1);
    //                 parse(_tmAction1, true);
    //             }

            uint8_t wDay =  wday();

            BLINKER_LOG_ALL(hour(), ":", minute(), ":", second());

            uint16_t nowMins = hour() * 60 + minute();

            if (triggedTask < BLINKER_TIMING_TIMER_SIZE && \
                nowMins != timingTask[triggedTask]->getTime())
            {
                BLINKER_LOG_ALL(BLINKER_F("timing trigged, now minutes check error!"));

                freshTiming(wDay, nowMins);

                return false;
            }

            if (triggedTask < BLINKER_TIMING_TIMER_SIZE)
            {
                // String _tmAction = timingTask[triggedTask]->getAction();
                char _tmAction[BLINKER_TIMER_TIMING_ACTION_SIZE];

                strcpy(_tmAction, timingTask[triggedTask]->getAction());

                BLINKER_LOG(BLINKER_F("timing trigged, action is: "), _tmAction);

                #if defined(BLINKER_AT_MQTT)
                    BProto::serialPrint(_tmAction);
                #else
                    parse(_tmAction, true);
                #endif

                checkOverlapping(wDay, timingTask[triggedTask]->getTime());

                freshTiming(wDay, timingTask[triggedTask]->getTime());

                return true;
            }
            else
            {
                BLINKER_LOG_ALL(BLINKER_F("timing trigged, none action"));

                freshTiming(wDay, 0);

                return false;
            }
        }

        return false;
    }

    
    bool BlinkerApi::checkSMS()
    {
        if ((millis() - _smsTime) >= BLINKER_SMS_MSG_LIMIT || \
            _smsTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkPUSH()
    {
        if ((millis() - _pushTime) >= BLINKER_PUSH_MSG_LIMIT || \
            _pushTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkWECHAT()
    {
        if ((millis() - _wechatTime) >= BLINKER_WECHAT_MSG_LIMIT || \
            _wechatTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkWEATHER()
    {
        if ((millis() - _weatherTime) >= BLINKER_WEATHER_MSG_LIMIT || \
            _weatherTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkAQI()
    {
        if ((millis() - _aqiTime) >= BLINKER_AQI_MSG_LIMIT || \
            _aqiTime == 0) return true;
        else return false;
    }

    
    void BlinkerApi::autoStart()
    {
        uint8_t checkData;

        EEPROM.begin(BLINKER_EEP_SIZE);
        EEPROM.get(BLINKER_EEP_ADDR_CHECK, checkData);
        if (checkData != BLINKER_CHECK_DATA)
        {
            for (uint16_t _addr = BLINKER_EEP_ADDR_AUTO_START;
                _addr < BLINKER_EEP_ADDR_AUTO_START + 
                BLINKER_ONE_AUTO_DATA_SIZE * 2; _addr++)
            {
                EEPROM.put(_addr, "\0");
            }
            EEPROM.put(BLINKER_EEP_ADDR_CHECK, BLINKER_CHECK_DATA);
            EEPROM.commit();
            EEPROM.end();
            return;
        }
        EEPROM.get(BLINKER_EEP_ADDR_AUTONUM, _aCount);
        if (_aCount > 2)
        {
            _aCount = 0;
            EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
        }
        EEPROM.commit();
        EEPROM.end();
        
        BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);

        if (_aCount)
        {
            for (uint8_t _num = 0; _num < _aCount; _num++)
            {
                BLINKER_LOG_ALL(BLINKER_F("new BlinkerAUTO() _num: "), _num);
                
                _AUTO[_num] = new BlinkerAUTO();
                _AUTO[_num]->setNum(_num);
                _AUTO[_num]->deserialization();
            }
        }
    }

    
    bool BlinkerApi::autoManager(const JsonObject& data)
    {
        // String set;
        bool isSet = false;
        bool isAuto = false;

        // isSet = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_SET);
        // isAuto = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_AUTO);
        isSet = data.containsKey(BLINKER_CMD_SET);
        String aData = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO];
        String aDataArray = data[BLINKER_CMD_AUTO][0];

        if (aData.length()) isAuto = true;

        if (aDataArray.length() && !isAuto)
        {
            for (uint8_t num = 0; num < 2; num++)
            {
                uint32_t _autoId = data[BLINKER_CMD_AUTO][num][BLINKER_CMD_AUTOID];
                String arrayData = data[BLINKER_CMD_AUTO][num];

                if (_aCount)
                {
                    for (uint8_t _num = 0; _num < _aCount; _num++)
                    {
                        if (_AUTO[_num]->id() == _autoId) {
                            _AUTO[_num]->manager(arrayData);
                            return true;
                        }
                    }
                    if (_aCount == 1)
                    {
                        _AUTO[_aCount] = new BlinkerAUTO();
                        _AUTO[_aCount]->setNum(_aCount);
                        _AUTO[_aCount]->manager(arrayData);

                        // _aCount = 1;
                        _aCount++;
                        EEPROM.begin(BLINKER_EEP_SIZE);
                        EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                        EEPROM.commit();
                        EEPROM.end();

                        BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                        // static_cast<Proto*>(this)->_print(autoData(), false);
                        // return true;
                    }
                    else
                    {
                        _AUTO[_aCount - 1]->manager(arrayData);
                        // return true;
                    }
                }
                else
                {
                    _AUTO[_aCount] = new BlinkerAUTO();
                    _AUTO[_aCount]->setNum(_aCount);
                    _AUTO[_aCount]->manager(arrayData);

                    _aCount = 1;
                    // _aCount++;
                    EEPROM.begin(BLINKER_EEP_SIZE);
                    EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                    EEPROM.commit();
                    EEPROM.end();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                    // static_cast<Proto*>(this)->_print(autoData(), false);
                    // return true;
                }
            }
            return true;
        }
        else if (isSet && isAuto)
        {
            _fresh = true;
            
            BLINKER_LOG_ALL(BLINKER_F("get auto setting"));
            
            bool isDelet = STRING_contains_string(BProto::dataParse(), BLINKER_CMD_DELETID);
            String isTriggedArray = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO]
                                        [BLINKER_CMD_ACTION][0];

            if (isDelet)
            {
                // uint32_t _autoId = STRING_find_numberic_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_DELETID);
                uint32_t _autoId = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO][BLINKER_CMD_DELETE];

                if (_aCount)
                {
                    for (uint8_t _num = 0; _num < _aCount; _num++)
                    {
                        if (_AUTO[_num]->id() == _autoId)
                        {
                            // _AUTO[_num]->manager(static_cast<Proto*>(this)->dataParse());
                            for (uint8_t a_num = _num; a_num < _aCount; a_num++)
                            {
                                if (a_num < _aCount - 1)
                                {
                                    _AUTO[a_num]->setNum(a_num + 1);
                                    _AUTO[a_num]->deserialization();
                                    _AUTO[a_num]->setNum(a_num);
                                    _AUTO[a_num]->serialization();
                                }
                                else{
                                    _num = _aCount;
                                }
                            }
                            _aCount--;

                            EEPROM.begin(BLINKER_EEP_SIZE);
                            EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                            EEPROM.commit();
                            EEPROM.end();
                            
                            BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                            
                            return true;
                        }
                    }
                }
            }
            else if(isTriggedArray.length())
            {
                for (uint8_t a_num = 0; a_num < BLINKER_MAX_WIDGET_SIZE; a_num++)
                {
                    String _autoData_array = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO]
                                                [BLINKER_CMD_ACTION][a_num];

                    if(_autoData_array.length())
                    {
                        DynamicJsonBuffer _jsonBuffer;
                        JsonObject& _array = _jsonBuffer.parseObject(_autoData_array);

                        json_parse(_array);
                        timerManager(_array, true);
                    }
                    else
                    {
                        // a_num = BLINKER_MAX_WIDGET_SIZE;
                        return true;
                    }
                }
            }
            else
            {
                // uint32_t _autoId = STRING_find_numberic_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_AUTOID);
                uint32_t _autoId = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO][BLINKER_CMD_AUTOID];

                // _aCount = 0;

                if (_aCount)
                {
                    for (uint8_t _num = 0; _num < _aCount; _num++)
                    {
                        if (_AUTO[_num]->id() == _autoId)
                        {
                            _AUTO[_num]->manager(BProto::dataParse());
                            return true;
                        }
                    }
                    if (_aCount == 1)
                    {
                        _AUTO[_aCount] = new BlinkerAUTO();
                        _AUTO[_aCount]->setNum(_aCount);
                        _AUTO[_aCount]->manager(BProto::dataParse());

                        // _aCount = 1;
                        _aCount++;
                        EEPROM.begin(BLINKER_EEP_SIZE);
                        EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                        EEPROM.commit();
                        EEPROM.end();
                        
                        BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                        
                        // static_cast<Proto*>(this)->_print(autoData(), false);
                        // return true;
                    }
                    else
                    {
                        _AUTO[_aCount - 1]->manager(BProto::dataParse());
                        // return true;
                    }
                }
                else
                {
                    _AUTO[_aCount] = new BlinkerAUTO();
                    _AUTO[_aCount]->setNum(_aCount);
                    _AUTO[_aCount]->manager(BProto::dataParse());

                    _aCount = 1;
                    // _aCount++;
                    EEPROM.begin(BLINKER_EEP_SIZE);
                    EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                    EEPROM.commit();
                    EEPROM.end();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                    
                    // static_cast<Proto*>(this)->_print(autoData(), false);
                    // return true;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    
    void BlinkerApi::otaPrase(const JsonObject& data)
    {
        if (data.containsKey(BLINKER_CMD_SET))
        {
            String value = data[BLINKER_CMD_SET];

            DynamicJsonBuffer jsonBufferSet;
            JsonObject& rootSet = jsonBufferSet.parseObject(value);

            if (!rootSet.success()) {
                // BLINKER_ERR_LOG_ALL("Json error");
                return;
            }

            if (rootSet.containsKey(BLINKER_CMD_UPDATE))
            {
                _fresh = true;
                
                ota();
            }
        }
    }

    
    bool BlinkerApi::checkCUPDATE()
    {
        if ((millis() - _cUpdateTime) >= BLINKER_CONFIG_UPDATE_LIMIT || \
            _cUpdateTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkCGET()
    {
        if ((millis() - _cGetTime) >= BLINKER_CONFIG_GET_LIMIT || \
            _cGetTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkCDEL()
    {
        if ((millis() - _cDelTime) >= BLINKER_CONFIG_GET_LIMIT || \
            _cDelTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkDataUpdata()
    {
        if ((millis() - _dUpdateTime) >= BLINKER_CONFIG_UPDATE_LIMIT * 60 || \
            _dUpdateTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkDataGet()
    {
        if ((millis() - _dGetTime) >= BLINKER_CONFIG_UPDATE_LIMIT || \
            _dGetTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkDataDel()
    {
        if ((millis() - _dDelTime) >= BLINKER_CONFIG_UPDATE_LIMIT || \
            _dDelTime == 0) return true;
        else return false;
    }

    
    bool BlinkerApi::checkAutoPull()
    {
        if ((millis() - _autoPullTime) >= 60000 || \
            _autoPullTime == 0) return true;
        else return false;
    }

    
    String BlinkerApi::bridgeQuery(char * key)
    {
        String data = BLINKER_F("/query?");
        data += BLINKER_F("deviceName=");
        data += BProto::deviceName();
        data += BLINKER_F("&bridgeKey=");
        data += STRING_format(key);

        return blinkerServer(BLINKER_CMD_BRIDGE_NUMBER, data);
    }

    String BlinkerApi::postServer(const String & url, const String & host, int port, const String & msg)
    {

        String client_msg;

        client_msg = BLINKER_F("POST ");
        client_msg += url;
        client_msg += BLINKER_F(" HTTP/1.1\r\nHost: ");
        client_msg += host;
        client_msg += BLINKER_F(":");
        client_msg += STRING_format(port);
        client_msg += BLINKER_F("\r\nContent-Type: application/json;charset=utf-8\r\nContent-Length: ");
        client_msg += STRING_format(msg.length());
        client_msg += BLINKER_F("\r\nConnection: Keep Alive\r\n\r\n");
        client_msg += msg;
        client_msg += BLINKER_F("\r\n");

        // client_s.print(client_msg);

        BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);

        return client_msg;
    }

    
    String BlinkerApi::getServer(const String & url, const String & host, int port)
    {
        String client_msg;

        client_msg = BLINKER_F("GET ");
        client_msg += url;
        client_msg += BLINKER_F(" HTTP/1.1\r\nHost: ");
        client_msg += host;
        client_msg += BLINKER_F(":");
        client_msg += STRING_format(port);
        client_msg += BLINKER_F("\r\nConnection: close\r\n\r\n");

        // client_s.print(client_msg);

        BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);

        return client_msg;
    }

    
    String BlinkerApi::blinkerServer(uint8_t _type, const String & msg, bool state)
    {
        switch (_type)
        {
            case BLINKER_CMD_SMS_NUMBER :
                if (!checkSMS()) {
                    return BLINKER_CMD_FALSE;
                }

                if ((!state && msg.length() > BLINKER_SMS_MAX_SEND_SIZE) ||
                    (state && msg.length() > BLINKER_SMS_MAX_SEND_SIZE + 15)) {
                    return BLINKER_CMD_FALSE;
                }
                break;
            case BLINKER_CMD_PUSH_NUMBER :
                if (!checkPUSH()) {
                    return BLINKER_CMD_FALSE;
                }
                break;
            case BLINKER_CMD_WECHAT_NUMBER :
                if (!checkWECHAT()) {
                    return BLINKER_CMD_FALSE;
                }
                break;
            case BLINKER_CMD_WEATHER_NUMBER :
                if (!checkWEATHER()) {
                    return BLINKER_CMD_FALSE;
                }
                break;
            case BLINKER_CMD_AQI_NUMBER :
                if (!checkAQI()) {
                    return BLINKER_CMD_FALSE;
                }
                break;
            case BLINKER_CMD_BRIDGE_NUMBER :
                break;
            #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
                    if (!checkCUPDATE()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_CONFIG_GET_NUMBER :
                    if (!checkCGET()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_CONFIG_DELETE_NUMBER :
                    if (!checkCDEL()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_DATA_STORAGE_NUMBER :
                    // if (!checkDataUpdata()) {
                    //     return BLINKER_CMD_FALSE;
                    // }
                    break;
                case BLINKER_CMD_DATA_GET_NUMBER :
                    if (!checkDataGet()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_DATA_DELETE_NUMBER :
                    if (!checkDataDel()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_AUTO_PULL_NUMBER :
                    if (!checkAutoPull()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_OTA_NUMBER :
                    break;
                case BLINKER_CMD_OTA_STATUS_NUMBER :
                    break;
            #endif
            default :
                return BLINKER_CMD_FALSE;
        }

        BLINKER_LOG_ALL(BLINKER_F("message: "), msg);

        // #ifndef BLINKER_LAN_DEBUG
        //     const int httpsPort = 443;
        // #elif defined(BLINKER_LAN_DEBUG)
        //     const int httpsPort = 9090;
        // #endif

        // #if defined(ESP8266)
        //     #ifndef BLINKER_LAN_DEBUG
        //         String host = BLINKER_F("iotdev.clz.me");
        //     #elif defined(BLINKER_LAN_DEBUG)
        //         String host = BLINKER_F("192.168.1.121");
        //     #endif
        //         String fingerprint = BLINKER_F("84 5f a4 8a 70 5e 79 7e f5 b3 b4 20 45 c8 35 55 72 f6 85 5a");
        //     #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        //         #ifndef BLINKER_LAN_DEBUG
        //             // #if defined(BLINKER_MQTT)
        //                 extern BearSSL::WiFiClientSecure client_mqtt;
        //             // #elif defined(BLINKER_PRO)
        //             //     extern BearSSL::WiFiClientSecure client_pro;
        //             // #elif defined(BLINKER_AT_MQTT)
        //             //     extern BearSSL::WiFiClientSecure client_mqtt_at;
        //             // #endif
        //             BearSSL::WiFiClientSecure client_s;
        //             // extern WiFiClientSecure client_mqtt;
        //         #elif defined(BLINKER_LAN_DEBUG)
        //             WiFiClient client_s;
        //         #endif
        //     #endif

        //     // #if defined(BLINKER_WIFI)
        //         // BearSSL::WiFiClientSecure client_s;
        //     // #endif

        //     BLINKER_LOG_ALL(BLINKER_F("connecting to "), host);
            
        //     uint8_t connet_times = 0;

        //     #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        //         client_mqtt.stop();
        //     // #elif defined(BLINKER_PRO)
        //     //     client_pro.stop();
        //     // #elif defined(BLINKER_AT_MQTT)
        //     //     client_mqtt_at.stop();
        //     #endif

        //     ::delay(100);

        //     bool mfln = client_s.probeMaxFragmentLength(host, httpsPort, 1024);
        //     if (mfln) {
        //         client_s.setBufferSizes(1024, 1024);
        //     }

        //     // client_s.setFingerprint(fingerprint.c_str());

        //     client_s.setInsecure();

        //     while (1) {
        //         bool cl_connected = false;
        //         if (!client_s.connect(host, httpsPort)) {
        //     // #ifdef BLINKER_DEBUG_ALL
        //             BLINKER_ERR_LOG(BLINKER_F("server connection failed"));
        //     // #endif
        //             // return BLINKER_CMD_FALSE;

        //             // connet_times++;
        //             ::delay(1000);
        //         }
        //         else {
        //             BLINKER_LOG_ALL(BLINKER_F("connection succeed"));
        //             // return true;
        //             cl_connected = true;

        //             break;
        //         }

        //         // if (connet_times >= 4 && !cl_connected)  return BLINKER_CMD_FALSE;
        //     }

        //     String url;
        //     // String client_msg;

        //     switch (_type) {
        //         case BLINKER_CMD_SMS_NUMBER :
        //             url = BLINKER_F("/api/v1/user/device/sms");
        //             client_s.print(postServer(url, host, httpsPort, msg));
        //             break;
        //         case BLINKER_CMD_PUSH_NUMBER :
        //             url = BLINKER_F("/api/v1/user/device/push");
        //             client_s.print(postServer(url, host, httpsPort, msg));
        //             break;
        //         case BLINKER_CMD_WECHAT_NUMBER :
        //             url = BLINKER_F("/api/v1/user/device/wxMsg/");
        //             client_s.print(postServer(url, host, httpsPort, msg));
        //             // return BLINKER_CMD_FALSE;
        //             break;
        //         case BLINKER_CMD_WEATHER_NUMBER :
        //             url = BLINKER_F("/api/v1");
        //             url += msg;
        //             client_s.print(getServer(url, host, httpsPort));
        //             break;
        //         case BLINKER_CMD_AQI_NUMBER :
        //             url = BLINKER_F("/api/v1");
        //             url += msg;
        //             client_s.print(getServer(url, host, httpsPort));
        //             break;
        //         case BLINKER_CMD_BRIDGE_NUMBER :
        //             url = BLINKER_F("/api/v1/user/device");
        //             url += msg;
        //             client_s.print(getServer(url, host, httpsPort));
        //             break;
        //         #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        //             case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
        //                 url = BLINKER_F("/api/v1/user/device/userconfig");
        //                 client_s.print(postServer(url, host, httpsPort, msg));
        //                 break;
        //             case BLINKER_CMD_CONFIG_GET_NUMBER :
        //                 url = BLINKER_F("/api/v1/user/device");
        //                 url += msg;
        //                 client_s.print(getServer(url, host, httpsPort));
        //                 break;
        //             case BLINKER_CMD_CONFIG_DELETE_NUMBER :
        //                 url = BLINKER_F("/api/v1/user/device");
        //                 url += msg;
        //                 client_s.print(getServer(url, host, httpsPort));
        //                 break;
        //             case BLINKER_CMD_DATA_STORAGE_NUMBER :
        //                 url = BLINKER_F("/api/v1/user/device/cloudStorage");
        //                 client_s.print(postServer(url, host, httpsPort, msg));
        //                 break;
        //             case BLINKER_CMD_DATA_GET_NUMBER :
        //                 url = BLINKER_F("/api/v1/user/device");
        //                 url += msg;
        //                 client_s.print(getServer(url, host, httpsPort));
        //                 break;
        //             case BLINKER_CMD_DATA_DELETE_NUMBER :
        //                 url = BLINKER_F("/api/v1/user/device");
        //                 url += msg;
        //                 client_s.print(getServer(url, host, httpsPort));
        //                 break;
        //             case BLINKER_CMD_AUTO_PULL_NUMBER :
        //                 url = BLINKER_F("/api/v1/user/device");
        //                 url += msg;
        //                 client_s.print(getServer(url, host, httpsPort));
        //                 break;
        //             case BLINKER_CMD_OTA_NUMBER :
        //                 url = BLINKER_F("/api/v1/user/device");
        //                 url += msg;
        //                 client_s.print(getServer(url, host, httpsPort));
        //                 break;
        //             case BLINKER_CMD_OTA_STATUS_NUMBER :
        //                 url = BLINKER_F("/api/v1/user/device/ota/upgrade_status");
        //                 // url += msg;
        //                 client_s.print(postServer(url, host, httpsPort, msg));
        //                 break;
        //         #endif
        //         default :
        //             return BLINKER_CMD_FALSE;
        //     }

        //     unsigned long timeout = millis();
        //     while (client_s.available() == 0)
        //     {
        //         if (millis() - timeout > 5000)
        //         {
        //             BLINKER_LOG_ALL(BLINKER_F(">>> Client Timeout !"));
        //             client_s.stop();
        //             return BLINKER_CMD_FALSE;
        //         }
        //     }

        //     // Read all the lines of the reply from server and print them to Serial
        //     String _dataGet;
        //     String lastGet;
        //     String lengthOfJson;
        //     while (client_s.available())
        //     {
        //         // String line = client_s.readStringUntil('\r');
        //         _dataGet = client_s.readStringUntil('\n');

        //         if (_dataGet.startsWith("Content-Length: "))
        //         {
        //             int addr_start = _dataGet.indexOf(' ');
        //             int addr_end = _dataGet.indexOf('\0', addr_start + 1);
        //             lengthOfJson = _dataGet.substring(addr_start + 1, addr_end);
        //         }

        //         if (_dataGet == "\r")
        //         {
        //             BLINKER_LOG_ALL(BLINKER_F("headers received"));                
        //             break;
        //         }
        //     }

        //     for(int i=0;i<lengthOfJson.toInt();i++)
        //     {
        //         lastGet += (char)client_s.read();
        //     }

        //     _dataGet = lastGet;
            
        //     BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);            

        //     client_s.stop();
        //     client_s.flush();

        //     // client_mqtt.setInsecure();

        //     DynamicJsonBuffer jsonBuffer;
        //     JsonObject& data_rp = jsonBuffer.parseObject(_dataGet);

        //     if (data_rp.success())
        //     {
        //         uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
        //         if (msg_code != 1000)
        //         {
        //             String _detail = data_rp[BLINKER_CMD_DETAIL];
        //             BLINKER_ERR_LOG(_detail);
        //         }
        //         else
        //         {
        //             // String _dataGet_ = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
        //             if (_type == BLINKER_CMD_BRIDGE_NUMBER)
        //                 _dataGet = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DEVICENAME].as<String>();
        //             else if (_type == BLINKER_CMD_OTA_NUMBER)
        //                 _dataGet = data_rp[BLINKER_CMD_DETAIL].as<String>();
        //             else
        //                 _dataGet = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA].as<String>();
        //         }
        //     }

        //     BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);

        //     switch (_type)
        //     {
        //         case BLINKER_CMD_SMS_NUMBER :
        //             _smsTime = millis();                
        //             break;
        //         case BLINKER_CMD_PUSH_NUMBER :
        //             _pushTime = millis();
        //             break;
        //         case BLINKER_CMD_WECHAT_NUMBER :
        //             _wechatTime = millis();
        //             break;
        //             // return BLINKER_CMD_FALSE;
        //         case BLINKER_CMD_WEATHER_NUMBER :
        //             _weatherTime = millis();
        //             break;
        //         case BLINKER_CMD_AQI_NUMBER :
        //             _aqiTime = millis();
        //             break;
        //         case BLINKER_CMD_BRIDGE_NUMBER :
        //             break;
        //         #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        //             case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
        //                 _cUpdateTime = millis();
        //                 break;
        //             case BLINKER_CMD_CONFIG_GET_NUMBER :
        //                 _cGetTime = millis();
        //                 break;
        //             case BLINKER_CMD_CONFIG_DELETE_NUMBER :
        //                 _cDelTime = millis();
        //                 break;
        //             case BLINKER_CMD_DATA_STORAGE_NUMBER :
        //                 _dUpdateTime = millis();
        //                 break;
        //             case BLINKER_CMD_DATA_GET_NUMBER :
        //                 _dGetTime = millis();
        //                 break;
        //             case BLINKER_CMD_DATA_DELETE_NUMBER :
        //                 _dDelTime = millis();
        //                 break;
        //             case BLINKER_CMD_AUTO_PULL_NUMBER :
        //                 _autoPullTime = millis();
        //                 break;
        //             case BLINKER_CMD_OTA_NUMBER :
        //                 break;
        //             case BLINKER_CMD_OTA_STATUS_NUMBER :
        //                 break;
        //         #endif
        //         default :
        //             return BLINKER_CMD_FALSE;
        //     }

        //     return _dataGet;
        // #elif defined(ESP32)
            #ifndef BLINKER_LAN_DEBUG
                String host = BLINKER_F("https://iotdev.clz.me");
            #elif defined(BLINKER_LAN_DEBUG)
                String host = BLINKER_F("http://192.168.1.121:9090");
            #endif

            // const char* ca = 
            //     "-----BEGIN CERTIFICATE-----\n" 
            //     "MIIEgDCCA2igAwIBAgIQDKTfhr9lmWbWUT0hjX36oDANBgkqhkiG9w0BAQsFADBy\n" 
            //     "MQswCQYDVQQGEwJDTjElMCMGA1UEChMcVHJ1c3RBc2lhIFRlY2hub2xvZ2llcywg\n" 
            //     "SW5jLjEdMBsGA1UECxMURG9tYWluIFZhbGlkYXRlZCBTU0wxHTAbBgNVBAMTFFRy\n" 
            //     "dXN0QXNpYSBUTFMgUlNBIENBMB4XDTE4MDEwNDAwMDAwMFoXDTE5MDEwNDEyMDAw\n" 
            //     "MFowGDEWMBQGA1UEAxMNaW90ZGV2LmNsei5tZTCCASIwDQYJKoZIhvcNAQEBBQAD\n" 
            //     "ggEPADCCAQoCggEBALbOFn7cJ2I/FKMJqIaEr38n4kCuJCCeNf1bWdWvOizmU2A8\n" 
            //     "QeTAr5e6Q3GKeJRdPnc8xXhqkTm4LOhgdZB8KzuVZARtu23D4vj4sVzxgC/zwJlZ\n" 
            //     "MRMxN+cqI37kXE8gGKW46l2H9vcukylJX+cx/tjWDfS2YuyXdFuS/RjhCxLgXzbS\n" 
            //     "cve1W0oBZnBPRSMV0kgxTWj7hEGZNWKIzK95BSCiMN59b+XEu3NWGRb/VzSAiJEy\n" 
            //     "Hy9DcDPBC9TEg+p5itHtdMhy2gq1OwsPgl9HUT0xmDATSNEV2RB3vwviNfu9/Eif\n" 
            //     "ObhsV078zf30TqdiESqISEB68gJ0Otru67ePoTkCAwEAAaOCAWowggFmMB8GA1Ud\n" 
            //     "IwQYMBaAFH/TmfOgRw4xAFZWIo63zJ7dygGKMB0GA1UdDgQWBBR/KLqnke61779P\n" 
            //     "xc9htonQwLOxPDAYBgNVHREEETAPgg1pb3RkZXYuY2x6Lm1lMA4GA1UdDwEB/wQE\n" 
            //     "AwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwTAYDVR0gBEUwQzA3\n" 
            //     "BglghkgBhv1sAQIwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQu\n" 
            //     "Y29tL0NQUzAIBgZngQwBAgEwgYEGCCsGAQUFBwEBBHUwczAlBggrBgEFBQcwAYYZ\n" 
            //     "aHR0cDovL29jc3AyLmRpZ2ljZXJ0LmNvbTBKBggrBgEFBQcwAoY+aHR0cDovL2Nh\n" 
            //     "Y2VydHMuZGlnaXRhbGNlcnR2YWxpZGF0aW9uLmNvbS9UcnVzdEFzaWFUTFNSU0FD\n" 
            //     "QS5jcnQwCQYDVR0TBAIwADANBgkqhkiG9w0BAQsFAAOCAQEAhtM4eyrWB14ajJpQ\n" 
            //     "ibZ5FbzVuvv2Le0FOSoss7UFCDJUYiz2LiV8yOhL4KTY+oVVkqHaYtcFS1CYZNzj\n" 
            //     "6xWcqYZJ+pgsto3WBEgNEEe0uLSiTW6M10hm0LFW9Det3k8fqwSlljqMha3gkpZ6\n" 
            //     "8WB0f2clXOuC+f1SxAOymnGUsSqbU0eFSgevcOIBKR7Hr3YXBXH3jjED76Q52OMS\n" 
            //     "ucfOM9/HB3jN8o/ioQbkI7xyd/DUQtzK6hSArEoYRl3p5H2P4fr9XqmpoZV3i3gQ\n" 
            //     "oOdVycVtpLunyUoVAB2DcOElfDxxXCvDH3XsgoIU216VY03MCaUZf7kZ2GiNL+UX\n" 
            //     "9UBd0Q==\n" 
            //     "-----END CERTIFICATE-----\n";
        // #endif

        #if defined(ESP8266)
            extern BearSSL::WiFiClientSecure client_mqtt;
            client_mqtt.stop();

            std::unique_ptr<BearSSL::WiFiClientSecure>client_s(new BearSSL::WiFiClientSecure);

            // client_s->setFingerprint(fingerprint);
            client_s->setInsecure();
        #endif

            HTTPClient http;

            String url_iot;

            int httpCode;

            // if (_type == BLINKER_CMD_SMS_NUMBER) {
            //     url_iot = String(host) + "/api/v1/user/device/sms";
            // }
            String conType = BLINKER_F("Content-Type");
            String application = BLINKER_F("application/json;charset=utf-8");

            switch (_type) {
                case BLINKER_CMD_SMS_NUMBER :
                    url_iot = host;
                    url_iot += BLINKER_F("/api/v1/user/device/sms");

                    #if defined(ESP8266)
                        http.begin(*client_s, url_iot);
                    #else
                        http.begin(url_iot);
                    #endif

                    http.addHeader(conType, application);
                    httpCode = http.POST(msg);
                    break;
                case BLINKER_CMD_PUSH_NUMBER :
                    url_iot = host;
                    url_iot += BLINKER_F("/api/v1/user/device/push");

                    #if defined(ESP8266)
                        http.begin(*client_s, url_iot);
                    #else
                        http.begin(url_iot);
                    #endif
                    
                    http.addHeader(conType, application);
                    httpCode = http.POST(msg);
                    break;
                    // return BLINKER_CMD_FALSE;
                case BLINKER_CMD_WECHAT_NUMBER :
                    url_iot = host;
                    url_iot += BLINKER_F("/api/v1/user/device/wxMsg/");

                    #if defined(ESP8266)
                        http.begin(*client_s, url_iot);
                    #else
                        http.begin(url_iot);
                    #endif
                    
                    http.addHeader(conType, application);
                    httpCode = http.POST(msg);
                    break;
                    // return BLINKER_CMD_FALSE;
                case BLINKER_CMD_WEATHER_NUMBER :
                    url_iot = host;
                    url_iot += BLINKER_F("/api/v1");
                    url_iot += msg;

                    #if defined(ESP8266)
                        http.begin(*client_s, url_iot);
                    #else
                        http.begin(url_iot);
                    #endif
                    
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_AQI_NUMBER :
                    url_iot = host;
                    url_iot += BLINKER_F("/api/v1");
                    url_iot += msg;

                    #if defined(ESP8266)
                        http.begin(*client_s, url_iot);
                    #else
                        http.begin(url_iot);
                    #endif
                    
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_BRIDGE_NUMBER :
                    url_iot = host;
                    url_iot += BLINKER_F("/api/v1/user/device");
                    url_iot += msg;

                    #if defined(ESP8266)
                        http.begin(*client_s, url_iot);
                    #else
                        http.begin(url_iot);
                    #endif
                    
                    httpCode = http.GET();
                    break;
                #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                    case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
                        url_iot = host;
                        url_iot += BLINKER_F("/api/v1/user/device/userconfig");

                        #if defined(ESP8266)
                            http.begin(*client_s, url_iot);
                        #else
                            http.begin(url_iot);
                        #endif
                        
                        http.addHeader(conType, application);
                        httpCode = http.POST(msg);
                        break;
                    case BLINKER_CMD_CONFIG_GET_NUMBER :
                        url_iot = host;
                        url_iot += BLINKER_F("/api/v1/user/device");
                        url_iot += msg;

                        #if defined(ESP8266)
                            http.begin(*client_s, url_iot);
                        #else
                            http.begin(url_iot);
                        #endif
                        
                        httpCode = http.GET();
                        break;
                    case BLINKER_CMD_CONFIG_DELETE_NUMBER :
                        url_iot = host;
                        url_iot += BLINKER_F("/api/v1/user/device");
                        url_iot += msg;

                        #if defined(ESP8266)
                            http.begin(*client_s, url_iot);
                        #else
                            http.begin(url_iot);
                        #endif
                        
                        httpCode = http.GET();
                        break;
                    case BLINKER_CMD_DATA_STORAGE_NUMBER :
                        url_iot = host;
                        url_iot += BLINKER_F("/api/v1/user/device/cloudStorage");

                        #if defined(ESP8266)
                            http.begin(*client_s, url_iot);
                        #else
                            http.begin(url_iot);
                        #endif
                        
                        http.addHeader(conType, application);
                        httpCode = http.POST(msg);
                        break;
                    case BLINKER_CMD_DATA_GET_NUMBER :
                        url_iot = host;
                        url_iot += BLINKER_F("/api/v1/user/device");
                        url_iot += msg;

                        #if defined(ESP8266)
                            http.begin(*client_s, url_iot);
                        #else
                            http.begin(url_iot);
                        #endif
                        
                        httpCode = http.GET();
                        break;
                    case BLINKER_CMD_DATA_DELETE_NUMBER :
                        url_iot = host;
                        url_iot += BLINKER_F("/api/v1/user/device");
                        url_iot += msg;

                        #if defined(ESP8266)
                            http.begin(*client_s, url_iot);
                        #else
                            http.begin(url_iot);
                        #endif
                        
                        httpCode = http.GET();
                        break;
                    case BLINKER_CMD_AUTO_PULL_NUMBER :
                        url_iot = host;
                        url_iot += BLINKER_F("/api/v1/user/device");
                        url_iot += msg;

                        #if defined(ESP8266)
                            http.begin(*client_s, url_iot);
                        #else
                            http.begin(url_iot);
                        #endif
                        
                        httpCode = http.GET();
                        break;
                    case BLINKER_CMD_OTA_NUMBER :
                        url_iot = host;
                        url_iot += BLINKER_F("/api/v1/user/device");
                        url_iot += msg;

                        #if defined(ESP8266)
                            http.begin(*client_s, url_iot);
                        #else
                            http.begin(url_iot);
                        #endif
                        
                        httpCode = http.GET();
                        break;
                    case BLINKER_CMD_OTA_STATUS_NUMBER :
                        url_iot = host;
                        url_iot += BLINKER_F("/api/v1/user/device/ota/upgrade_status");

                        #if defined(ESP8266)
                            http.begin(*client_s, url_iot);
                        #else
                            http.begin(url_iot);
                        #endif
                        
                        http.addHeader(conType, application);
                        httpCode = http.POST(msg);
                        break;
                #endif
                default :
                    return BLINKER_CMD_FALSE;
            }
            
            BLINKER_LOG_ALL(BLINKER_F("HTTPS begin: "), url_iot);

            // http.begin(url_iot, ca); TODO
            // http.begin(url_iot);

            // http.addHeader("Content-Type", "application/json");

            // httpCode = http.POST(msg);
            
            BLINKER_LOG_ALL(BLINKER_F("HTTPS payload: "), msg);

            if (httpCode > 0) {
                BLINKER_LOG_ALL(BLINKER_F("[HTTP] status... code: "), httpCode);
                
                String payload;
                if (httpCode == HTTP_CODE_OK) {
                    payload = http.getString();
                    
                    BLINKER_LOG_ALL(payload);
                    
                    DynamicJsonBuffer jsonBuffer;
                    JsonObject& data_rp = jsonBuffer.parseObject(payload);

                    if (data_rp.success())
                    {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000)
                        {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else
                        {
                            // String _payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
                            // payload = _payload;

                            if (_type == BLINKER_CMD_BRIDGE_NUMBER)
                                payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DEVICENAME].as<String>();
                            else if (_type == BLINKER_CMD_OTA_NUMBER)
                                payload = data_rp[BLINKER_CMD_DETAIL].as<String>();
                            else
                                payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA].as<String>();
                        }
                    }

                    BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);

                    switch (_type) {
                        case BLINKER_CMD_SMS_NUMBER :
                            _smsTime = millis();
                            break;
                        case BLINKER_CMD_PUSH_NUMBER :
                            _pushTime = millis();
                            break;
                        case BLINKER_CMD_WECHAT_NUMBER :
                            _wechatTime = millis();
                            break;
                            // return BLINKER_CMD_FALSE;
                        case BLINKER_CMD_WEATHER_NUMBER :
                            _weatherTime = millis();
                            break;
                        case BLINKER_CMD_AQI_NUMBER :
                            _aqiTime = millis();
                            break;
                        case BLINKER_CMD_BRIDGE_NUMBER :
                            break;
                        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                            case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
                                _cUpdateTime = millis();
                                break;
                            case BLINKER_CMD_CONFIG_GET_NUMBER :
                                _cGetTime = millis();
                                break;
                            case BLINKER_CMD_CONFIG_DELETE_NUMBER :
                                _cDelTime = millis();
                                break;
                            case BLINKER_CMD_DATA_STORAGE_NUMBER :
                                _dUpdateTime = millis();
                                break;
                            case BLINKER_CMD_DATA_GET_NUMBER :
                                _dGetTime = millis();
                                break;
                            case BLINKER_CMD_DATA_DELETE_NUMBER :
                                _dDelTime = millis();
                                break;
                            case BLINKER_CMD_AUTO_PULL_NUMBER :
                                _autoPullTime = millis();
                                break;
                            case BLINKER_CMD_OTA_NUMBER :
                                break;
                            case BLINKER_CMD_OTA_STATUS_NUMBER :
                                break;
                        #endif
                        default :
                            return BLINKER_CMD_FALSE;
                    }
                }
                
                http.end();

                return payload;
            }
            else {
                BLINKER_LOG_ALL(BLINKER_F("[HTTP] ... failed, error: "), http.errorToString(httpCode).c_str());
                String payload = http.getString();
                BLINKER_LOG_ALL(payload);
                
                if (_type == BLINKER_CMD_SMS_NUMBER) {
                    _smsTime = millis();
                }
                http.end();
                return BLINKER_CMD_FALSE;
            }
        // #endif
    }
#endif

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO)// || defined(BLINKER_MQTT_AT)
    
    void BlinkerApi::aliParse(const String & _data)
    {
        BLINKER_LOG_ALL(BLINKER_F("AliGenie parse data: "), _data);

        DynamicJsonBuffer jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(_data);

        if (!root.success()) return;

        if (root.containsKey(BLINKER_CMD_GET))
        {
            String value = root[BLINKER_CMD_GET];

            if (value == BLINKER_CMD_STATE){
                if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_ALL_NUMBER);
            }
            else if (value == BLINKER_CMD_POWERSTATE) {
                if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_POWERSTATE_NUMBER);
            }
            else if (value == BLINKER_CMD_COLOR) {
                if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_COLOR_NUMBER);
            }
            else if (value == BLINKER_CMD_COLORTEMP) {
                if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_COLORTEMP_NUMBER);
            }
            else if (value == BLINKER_CMD_BRIGHTNESS) {
                if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_BRIGHTNESS_NUMBER);
            }
            else if (value == BLINKER_CMD_TEMP) {
                if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_TEMP_NUMBER);
            }
            else if (value == BLINKER_CMD_HUMI) {
                if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_HUMI_NUMBER);
            }
            else if (value == BLINKER_CMD_PM25) {
                if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_PM25_NUMBER);
            }
            else if (value == BLINKER_CMD_MODE) {
                if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_MODE_NUMBER);
            }
        }
        else if (root.containsKey(BLINKER_CMD_SET)) {
            String value = root[BLINKER_CMD_SET];

            DynamicJsonBuffer jsonBufferSet;
            JsonObject& rootSet = jsonBufferSet.parseObject(value);

            if (!rootSet.success()) {
                // BLINKER_ERR_LOG_ALL("Json error");
                return;
            }

            // BLINKER_LOG_ALL("Json parse success");

            if (rootSet.containsKey(BLINKER_CMD_POWERSTATE)) {
                String setValue = rootSet[BLINKER_CMD_POWERSTATE];

                if (_AliGeniePowerStateFunc) _AliGeniePowerStateFunc(setValue);
            }
            else if (rootSet.containsKey(BLINKER_CMD_COLOR)) {
                String setValue = rootSet[BLINKER_CMD_COLOR];

                if (_AliGenieSetColorFunc) _AliGenieSetColorFunc(setValue);
            }
            else if (rootSet.containsKey(BLINKER_CMD_BRIGHTNESS)) {
                String setValue = rootSet[BLINKER_CMD_BRIGHTNESS];

                if (_AliGenieSetBrightnessFunc) _AliGenieSetBrightnessFunc(setValue);
            }
            else if (rootSet.containsKey(BLINKER_CMD_UPBRIGHTNESS)) {
                String setValue = rootSet[BLINKER_CMD_UPBRIGHTNESS];

                if (_AliGenieSetRelativeBrightnessFunc) _AliGenieSetRelativeBrightnessFunc(setValue.toInt());
            }
            else if (rootSet.containsKey(BLINKER_CMD_DOWNBRIGHTNESS)) {
                String setValue = rootSet[BLINKER_CMD_DOWNBRIGHTNESS];

                if (_AliGenieSetRelativeBrightnessFunc) _AliGenieSetRelativeBrightnessFunc(- setValue.toInt());
            }
            else if (rootSet.containsKey(BLINKER_CMD_COLORTEMP)) {
                String setValue = rootSet[BLINKER_CMD_COLORTEMP];

                if (_AliGenieSetColorTemperature) _AliGenieSetColorTemperature(setValue.toInt());
            }
            else if (rootSet.containsKey(BLINKER_CMD_UPCOLORTEMP)) {
                String setValue = rootSet[BLINKER_CMD_UPCOLORTEMP];

                if (_AliGenieSetRelativeColorTemperature) _AliGenieSetRelativeColorTemperature(setValue.toInt());
            }
            else if (rootSet.containsKey(BLINKER_CMD_DOWNCOLORTEMP)) {
                String setValue = rootSet[BLINKER_CMD_DOWNCOLORTEMP];

                if (_AliGenieSetRelativeColorTemperature) _AliGenieSetRelativeColorTemperature(- setValue.toInt());
            }
            else if (rootSet.containsKey(BLINKER_CMD_MODE)) {
                String setMode = rootSet[BLINKER_CMD_MODE];

                if (_AliGenieSetModeFunc) _AliGenieSetModeFunc(setMode);
            }
            else if (rootSet.containsKey(BLINKER_CMD_CANCELMODE)) {
                String setcMode = rootSet[BLINKER_CMD_CANCELMODE];

                if (_AliGenieSetcModeFunc) _AliGenieSetcModeFunc(setcMode);
            }
        }
    }

    
    void BlinkerApi::duerParse(const String & _data)
    {
        BLINKER_LOG_ALL(BLINKER_F("DuerOS parse data: "), _data);

        DynamicJsonBuffer jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(_data);

        if (!root.success()) return;

        if (root.containsKey(BLINKER_CMD_GET))
        {
            String value = root[BLINKER_CMD_GET];

            if (value == BLINKER_CMD_AQI) {
                if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_AQI_NUMBER);
            }
            else if (value == BLINKER_CMD_PM25) {
                if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_PM25_NUMBER);
            }
            else if (value == BLINKER_CMD_PM10) {
                if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_PM10_NUMBER);
            }
            else if (value == BLINKER_CMD_CO2) {
                if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_CO2_NUMBER);
            }
            else if (value == BLINKER_CMD_TEMP) {
                if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_TEMP_NUMBER);
            }
            else if (value == BLINKER_CMD_HUMI) {
                if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_HUMI_NUMBER);
            }
            else if (value == BLINKER_CMD_MODE) {
                if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_MODE_NUMBER);
            }            
            else if (value == BLINKER_CMD_TIME_ALL) {
                if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_TIME_NUMBER);
            }
        }
        else if (root.containsKey(BLINKER_CMD_SET)) {
            String value = root[BLINKER_CMD_SET];

            DynamicJsonBuffer jsonBufferSet;
            JsonObject& rootSet = jsonBufferSet.parseObject(value);

            if (!rootSet.success()) {
                // BLINKER_ERR_LOG_ALL("Json error");
                return;
            }

            // BLINKER_LOG_ALL("Json parse success");

            if (rootSet.containsKey(BLINKER_CMD_POWERSTATE)) {
                String setValue = rootSet[BLINKER_CMD_POWERSTATE];

                if (_DuerOSPowerStateFunc) _DuerOSPowerStateFunc(setValue);
            }
            else if (rootSet.containsKey(BLINKER_CMD_COLOR)) {
                String setValue = rootSet[BLINKER_CMD_COLOR];

                if (_DuerOSSetColorFunc) _DuerOSSetColorFunc(setValue.toInt());
            }
            else if (rootSet.containsKey(BLINKER_CMD_BRIGHTNESS)) {
                String setValue = rootSet[BLINKER_CMD_BRIGHTNESS];

                if (_DuerOSSetBrightnessFunc) _DuerOSSetBrightnessFunc(setValue);
            }
            else if (rootSet.containsKey(BLINKER_CMD_UPBRIGHTNESS)) {
                String setValue = rootSet[BLINKER_CMD_UPBRIGHTNESS];

                if (_DuerOSSetRelativeBrightnessFunc) _DuerOSSetRelativeBrightnessFunc(setValue.toInt());
            }
            else if (rootSet.containsKey(BLINKER_CMD_DOWNBRIGHTNESS)) {
                String setValue = rootSet[BLINKER_CMD_DOWNBRIGHTNESS];

                if (_DuerOSSetRelativeBrightnessFunc) _DuerOSSetRelativeBrightnessFunc(- setValue.toInt());
            }
            // else if (rootSet.containsKey(BLINKER_CMD_COLORTEMP)) {
            //     String setValue = rootSet[BLINKER_CMD_COLORTEMP];

            //     if (_DuerOSSetColorTemperature) _DuerOSSetColorTemperature(setValue.toInt());
            // }
            // else if (rootSet.containsKey(BLINKER_CMD_UPCOLORTEMP)) {
            //     String setValue = rootSet[BLINKER_CMD_UPCOLORTEMP];

            //     if (_DuerOSSetRelativeColorTemperature) _DuerOSSetRelativeColorTemperature(setValue.toInt());
            // }
            // else if (rootSet.containsKey(BLINKER_CMD_DOWNCOLORTEMP)) {
            //     String setValue = rootSet[BLINKER_CMD_DOWNCOLORTEMP];

            //     if (_DuerOSSetRelativeColorTemperature) _DuerOSSetRelativeColorTemperature(- setValue.toInt());
            // }
            else if (rootSet.containsKey(BLINKER_CMD_MODE)) {
                String setMode = rootSet[BLINKER_CMD_MODE];

                if (_DuerOSSetModeFunc) _DuerOSSetModeFunc(setMode);
            }
            else if (rootSet.containsKey(BLINKER_CMD_CANCELMODE)) {
                String setcMode = rootSet[BLINKER_CMD_CANCELMODE];

                if (_DuerOSSetcModeFunc) _DuerOSSetcModeFunc(setcMode);
            }
        }
    }
#endif

#if defined(BLINKER_MQTT_AT)    
    void BlinkerApi::aliParse(const String & _data)
    {
        BLINKER_LOG_ALL(BLINKER_F("AliGenie parse data: "), _data);

        if (STRING_contains_string(_data, "vAssistant"))
        {
            String value = "";
            if (STRING_find_string_value(_data, value, BLINKER_CMD_GET))
            {
                if (value == BLINKER_CMD_STATE) {
                    if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_ALL_NUMBER);
                }
                else if (value == BLINKER_CMD_POWERSTATE) {
                    if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_POWERSTATE_NUMBER);
                }
                else if (value == BLINKER_CMD_COLOR) {
                    if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_COLOR_NUMBER);
                }
                else if (value == BLINKER_CMD_COLORTEMP) {
                    if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_COLORTEMP_NUMBER);
                }
                else if (value == BLINKER_CMD_BRIGHTNESS) {
                    if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_BRIGHTNESS_NUMBER);
                }
                else if (value == BLINKER_CMD_TEMP) {
                    if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_TEMP_NUMBER);
                }
                else if (value == BLINKER_CMD_HUMI) {
                    if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_HUMI_NUMBER);
                }
                else if (value == BLINKER_CMD_PM25) {
                    if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_PM25_NUMBER);
                }
                else if (value == BLINKER_CMD_MODE) {
                    if (_AliGenieQueryFunc) _AliGenieQueryFunc(BLINKER_CMD_QUERY_MODE_NUMBER);
                }
            }
            else if (STRING_contains_string(_data, BLINKER_CMD_SET))
            {
                if (STRING_find_string_value(_data, value, BLINKER_CMD_POWERSTATE))
                {
                    if (_AliGeniePowerStateFunc) _AliGeniePowerStateFunc(value);
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_COLOR))
                {
                    if (_AliGenieSetColorFunc) _AliGenieSetColorFunc(value);
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_BRIGHTNESS))
                {
                    if (_AliGenieSetBrightnessFunc) _AliGenieSetBrightnessFunc(value);
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_UPBRIGHTNESS))
                {
                    if (_AliGenieSetRelativeBrightnessFunc) _AliGenieSetRelativeBrightnessFunc(value.toInt());
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_DOWNBRIGHTNESS))
                {
                    if (_AliGenieSetRelativeBrightnessFunc) _AliGenieSetRelativeBrightnessFunc(- value.toInt());
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_COLORTEMP))
                {
                    if (_AliGenieSetColorTemperature) _AliGenieSetColorTemperature(value.toInt());
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_UPCOLORTEMP))
                {
                    if (_AliGenieSetRelativeColorTemperature) _AliGenieSetRelativeColorTemperature(value.toInt());
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_DOWNCOLORTEMP))
                {
                    if (_AliGenieSetRelativeColorTemperature) _AliGenieSetRelativeColorTemperature(- value.toInt());
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_MODE))
                {
                    if (_AliGenieSetModeFunc) _AliGenieSetModeFunc(value);
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_CANCELMODE))
                {
                    if (_AliGenieSetcModeFunc) _AliGenieSetcModeFunc(value);
                }
            }
        }
    }

    
    void BlinkerApi::duerParse(const String & _data)
    {
        BLINKER_LOG_ALL(BLINKER_F("DuerOS parse data: "), _data);

        if (STRING_contains_string(_data, "vAssistant"))
        {
            String value = "";
            if (STRING_find_string_value(_data, value, BLINKER_CMD_GET))
            {
                if (value == BLINKER_CMD_STATE) {
                    if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_ALL_NUMBER);
                }
                else if (value == BLINKER_CMD_POWERSTATE) {
                    if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_POWERSTATE_NUMBER);
                }
                else if (value == BLINKER_CMD_COLOR) {
                    if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_COLOR_NUMBER);
                }
                else if (value == BLINKER_CMD_COLORTEMP) {
                    if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_COLORTEMP_NUMBER);
                }
                else if (value == BLINKER_CMD_BRIGHTNESS) {
                    if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_BRIGHTNESS_NUMBER);
                }
                else if (value == BLINKER_CMD_TEMP) {
                    if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_TEMP_NUMBER);
                }
                else if (value == BLINKER_CMD_HUMI) {
                    if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_HUMI_NUMBER);
                }
                else if (value == BLINKER_CMD_PM25) {
                    if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_PM25_NUMBER);
                }
                else if (value == BLINKER_CMD_MODE) {
                    if (_DuerOSQueryFunc) _DuerOSQueryFunc(BLINKER_CMD_QUERY_MODE_NUMBER);
                }
            }
            else if (STRING_contains_string(_data, BLINKER_CMD_SET))
            {
                if (STRING_find_string_value(_data, value, BLINKER_CMD_POWERSTATE))
                {
                    if (_DuerOSPowerStateFunc) _DuerOSPowerStateFunc(value);
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_COLOR))
                {
                    if (_DuerOSSetColorFunc) _DuerOSSetColorFunc(value.toInt());
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_BRIGHTNESS))
                {
                    if (_DuerOSSetBrightnessFunc) _DuerOSSetBrightnessFunc(value);
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_UPBRIGHTNESS))
                {
                    if (_DuerOSSetRelativeBrightnessFunc) _DuerOSSetRelativeBrightnessFunc(value.toInt());
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_DOWNBRIGHTNESS))
                {
                    if (_DuerOSSetRelativeBrightnessFunc) _DuerOSSetRelativeBrightnessFunc(- value.toInt());
                }
                // else if (STRING_find_string_value(_data, value, BLINKER_CMD_COLORTEMP))
                // {
                //     if (_DuerOSSetColorTemperature) _DuerOSSetColorTemperature(value.toInt());
                // }
                // else if (STRING_find_string_value(_data, value, BLINKER_CMD_UPCOLORTEMP))
                // {
                //     if (_DuerOSSetRelativeColorTemperature) _DuerOSSetRelativeColorTemperature(value.toInt());
                // }
                // else if (STRING_find_string_value(_data, value, BLINKER_CMD_DOWNCOLORTEMP))
                // {
                //     if (_DuerOSSetRelativeColorTemperature) _DuerOSSetRelativeColorTemperature(- value.toInt());
                // }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_MODE))
                {
                    if (_DuerOSSetModeFunc) _DuerOSSetModeFunc(value);
                }
                else if (STRING_find_string_value(_data, value, BLINKER_CMD_CANCELMODE))
                {
                    if (_DuerOSSetcModeFunc) _DuerOSSetcModeFunc(value);
                }
            }
        }
    }
#endif

#if defined(BLINKER_AT_MQTT)    
    void BlinkerApi::atBegin()
    {
        while (_status == BL_BEGIN)
        {
            serialAvailable();
        }
    }
    
    void BlinkerApi::parseATdata()
    {
        String reqData;
        
        if (_slaverAT->cmd() == BLINKER_CMD_AT) {
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_RST) {
            BProto::serialPrint(BLINKER_CMD_OK);
            ::delay(100);
            ESP.restart();
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_GMR) {
            // reqData = "+" + STRING_format(BLINKER_CMD_GMR) + 
            //         "=<MQTT_CONFIG_MODE>,<MQTT_AUTH_KEY>" + 
            //         "[,<MQTT_WIFI_SSID>,<MQTT_WIFI_PSWD>]";
            BProto::serialPrint(BLINKER_ESP_AT_VERSION);
            BProto::serialPrint(BLINKER_VERSION);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_UART_CUR) {
            blinker_at_state_t at_state = _slaverAT->state();

            BLINKER_LOG(at_state);

            switch (at_state)
            {
                case AT_NONE:
                    // BProto::serialPrint();
                    break;
                case AT_TEST:
                    reqData = BLINKER_CMD_AT;// + 
                    reqData += BLINKER_F("+");
                    reqData += BLINKER_CMD_UART_CUR;// + 
                    reqData += BLINKER_F("=<baudrate>,<databits>,<stopbits>,<parity>");
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_QUERY:
                    reqData = BLINKER_F("+");
                    reqData += BLINKER_CMD_UART_CUR;
                    reqData += BLINKER_F(":");
                    reqData += STRING_format(serialSet >> 8 & 0x00FFFFFF);
                    reqData += BLINKER_F(",");
                    reqData += STRING_format(serialSet >> 4 & 0x0F);
                    reqData += BLINKER_F(",");
                    reqData += STRING_format(serialSet >> 2 & 0x03);
                    reqData += BLINKER_F(",");
                    reqData += STRING_format(serialSet      & 0x03);
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_SETTING:
                    BLINKER_LOG_ALL(BLINKER_F("SER_BAUD: "), _slaverAT->getParam(SER_BAUD));
                    BLINKER_LOG_ALL(BLINKER_F("SER_DBIT: "), _slaverAT->getParam(SER_DBIT));
                    BLINKER_LOG_ALL(BLINKER_F("SER_SBIT: "), _slaverAT->getParam(SER_SBIT));
                    BLINKER_LOG_ALL(BLINKER_F("SER_PRIT: "), _slaverAT->getParam(SER_PRIT));
                    if (BLINKER_UART_PARAM_NUM != _slaverAT->paramNum()) return;

                    serialSet = (_slaverAT->getParam(SER_BAUD)).toInt() << 8 |
                                (_slaverAT->getParam(SER_DBIT)).toInt() << 4 |
                                (_slaverAT->getParam(SER_SBIT)).toInt() << 2 |
                                (_slaverAT->getParam(SER_PRIT)).toInt();

                    ss_cfg = serConfig();

                    BLINKER_LOG_ALL(BLINKER_F("SER_PRIT: "), serialSet);

                    BProto::serialPrint(BLINKER_CMD_OK);

                    // if (isHWS) {
                        Serial.begin(serialSet >> 8 & 0x00FFFFFF, ss_cfg);
                    // }
                    // else {
                    //     SSerialBLE->begin(serialSet >> 8 & 0x00FFFFFF, ss_cfg);
                    // }
                    break;
                case AT_ACTION:
                    // BProto::serialPrint();
                    break;
                default :
                    break;
            }
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_UART_DEF) {
            blinker_at_state_t at_state = _slaverAT->state();

            BLINKER_LOG(at_state);

            switch (at_state)
            {
                case AT_NONE:
                    // BProto::serialPrint();
                    break;
                case AT_TEST:
                    reqData = BLINKER_CMD_AT;
                    reqData += BLINKER_F("+");
                    reqData += BLINKER_CMD_UART_DEF;
                    reqData += BLINKER_F("=<baudrate>,<databits>,<stopbits>,<parity>");
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_QUERY:
                    reqData = BLINKER_F("+");
                    reqData += BLINKER_CMD_UART_DEF;
                    reqData += BLINKER_F(":");
                    reqData += STRING_format(serialSet >> 8 & 0x00FFFFFF);
                    reqData += BLINKER_F(",");
                    reqData += STRING_format(serialSet >> 4 & 0x0F);
                    reqData += BLINKER_F(",");
                    reqData += STRING_format(serialSet >> 2 & 0x03);
                    reqData += BLINKER_F(",");
                    reqData += STRING_format(serialSet      & 0x03);
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_SETTING:
                    BLINKER_LOG_ALL(BLINKER_F("SER_BAUD: "), _slaverAT->getParam(SER_BAUD));
                    BLINKER_LOG_ALL(BLINKER_F("SER_DBIT: "), _slaverAT->getParam(SER_DBIT));
                    BLINKER_LOG_ALL(BLINKER_F("SER_SBIT: "), _slaverAT->getParam(SER_SBIT));
                    BLINKER_LOG_ALL(BLINKER_F("SER_PRIT: "), _slaverAT->getParam(SER_PRIT));
                    
                    if (BLINKER_UART_PARAM_NUM != _slaverAT->paramNum()) return;

                    serialSet = (_slaverAT->getParam(SER_BAUD)).toInt() << 8 |
                                (_slaverAT->getParam(SER_DBIT)).toInt() << 4 |
                                (_slaverAT->getParam(SER_SBIT)).toInt() << 2 |
                                (_slaverAT->getParam(SER_PRIT)).toInt();

                    ss_cfg = serConfig();

                    BLINKER_LOG_ALL(BLINKER_F("SER_PRIT: "), serialSet);

                    BProto::serialPrint(BLINKER_CMD_OK);

                    // if (isHWS) {
                        Serial.begin(serialSet >> 8 & 0x00FFFFFF, ss_cfg);
                    // }
                    // else {
                    //     SSerialBLE->begin(serialSet >> 8 & 0x00FFFFFF, ss_cfg);
                    // }

                    EEPROM.begin(BLINKER_EEP_SIZE);
                    EEPROM.put(BLINKER_EEP_ADDR_SERIALCFG, serialSet);
                    EEPROM.commit();
                    EEPROM.end();
                    break;
                case AT_ACTION:
                    // BProto::serialPrint();
                    break;
                default :
                    break;
            }
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_RAM && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_F(BLINKER_CMD_RAM);
            reqData += BLINKER_F(":");
            reqData += STRING_format(BLINKER_FreeHeap());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_ADC && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_ADC;
            reqData += BLINKER_F(":");
            reqData += STRING_format(analogRead(A0));
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_IOSETCFG && _slaverAT->state() == AT_SETTING) {
            BLINKER_LOG_ALL(BLINKER_F("PIN_SET: "), _slaverAT->getParam(PIN_SET));
            BLINKER_LOG_ALL(BLINKER_F("PIN_MODE: "), _slaverAT->getParam(PIN_MODE));
            BLINKER_LOG_ALL(BLINKER_F("PIN_PULLSTATE: "), _slaverAT->getParam(PIN_PULLSTATE));

            if (BLINKER_IOSETCFG_PARAM_NUM != _slaverAT->paramNum()) return;

            uint8_t set_pin = (_slaverAT->getParam(PIN_SET)).toInt();
            uint8_t set_mode = (_slaverAT->getParam(PIN_MODE)).toInt();
            uint8_t set_pull = (_slaverAT->getParam(PIN_PULLSTATE)).toInt();

            if (set_pin >= BLINKER_MAX_PIN_NUM || 
                set_mode > BLINKER_IO_OUTPUT_NUM ||
                set_pull > 2)
            {
                return;
            }

            if (pinDataNum == 0) {
                _pinData[pinDataNum] = new PinData(set_pin, set_mode, set_pull);
                pinDataNum++;
            }
            else {
                bool _isSet = false;
                for (uint8_t _num = 0; _num < pinDataNum; _num++)
                {
                    if (_pinData[_num]->checkPin(set_pin))
                    {
                        _isSet = true;
                        _pinData[_num]->fresh(set_mode, set_pull);
                    }
                }
                if (!_isSet) {
                    _pinData[pinDataNum] = new PinData(set_pin, set_mode, set_pull);
                    pinDataNum++;
                }
            }
            
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_IOGETCFG && _slaverAT->state() == AT_SETTING) {
            BLINKER_LOG_ALL(BLINKER_F("PIN_SET: "), _slaverAT->getParam(PIN_SET));

            if (BLINKER_IOGETCFG_PARAM_NUM != _slaverAT->paramNum()) return;

            uint8_t set_pin = (_slaverAT->getParam(PIN_SET)).toInt();

            if (set_pin >= BLINKER_MAX_PIN_NUM) return;

            bool _isGet = false;
            for (uint8_t _num = 0; _num < pinDataNum; _num++)
            {
                if (_pinData[_num]->checkPin(set_pin))
                {
                    _isGet = true;
                    reqData = BLINKER_F("+");
                    reqData += BLINKER_CMD_IOGETCFG;
                    reqData += BLINKER_F(":");
                    reqData += _pinData[_num]->data();
                    BProto::serialPrint(reqData);
                }
            }
            if (!_isGet) {
                reqData = BLINKER_F("+");
                reqData += BLINKER_CMD_IOGETCFG;
                reqData += BLINKER_F(":");
                reqData += _slaverAT->getParam(PIN_SET);
                reqData += BLINKER_F(",2,0");
                BProto::serialPrint(reqData);
            }

            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_GPIOWRITE && _slaverAT->state() == AT_SETTING) {
            BLINKER_LOG_ALL(BLINKER_F("IO_PIN: "), _slaverAT->getParam(IO_PIN));
            BLINKER_LOG_ALL(BLINKER_F("IO_LVL: "),  _slaverAT->getParam(IO_LVL));

            if (BLINKER_GPIOWRITE_PARAM_NUM != _slaverAT->paramNum()) return;

            uint8_t set_pin = (_slaverAT->getParam(IO_PIN)).toInt();
            uint8_t set_lvl = (_slaverAT->getParam(IO_LVL)).toInt();

            if (set_pin >= BLINKER_MAX_PIN_NUM) return;

            // bool _isSet = false;
            for (uint8_t _num = 0; _num < pinDataNum; _num++)
            {
                if (_pinData[_num]->checkPin(set_pin))
                {
                    if (_pinData[_num]->getMode() == BLINKER_IO_OUTPUT_NUM)
                    {
                        if (set_lvl <= 1) {
                            digitalWrite(set_pin, set_lvl ? HIGH : LOW);
                            BProto::serialPrint(BLINKER_CMD_OK);
                            return;
                        }
                    }
                }
            }

            BProto::serialPrint(BLINKER_CMD_ERROR);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_GPIOWREAD && _slaverAT->state() == AT_SETTING) {
            BLINKER_LOG_ALL(BLINKER_F("IO_PIN: "), _slaverAT->getParam(IO_PIN));

            if (BLINKER_GPIOREAD_PARAM_NUM != _slaverAT->paramNum()) return;

            uint8_t set_pin = (_slaverAT->getParam(IO_PIN)).toInt();

            if (set_pin >= BLINKER_MAX_PIN_NUM)
            {
                BProto::serialPrint(BLINKER_CMD_ERROR);
                return;
            }

            // bool _isSet = false;
            for (uint8_t _num = 0; _num < pinDataNum; _num++)
            {
                if (_pinData[_num]->checkPin(set_pin))
                {
                    // if (_pinData[_num]->getMode() == BLINKER_IO_INPUT_NUM)
                    // {
                    //     if (set_lvl <= 1) {
                            reqData = BLINKER_F("+");
                            reqData += BLINKER_CMD_GPIOWREAD;
                            reqData += BLINKER_F(":");
                            reqData += STRING_format(set_pin);
                            reqData += BLINKER_F(",");
                            reqData += STRING_format(_pinData[_num]->getMode());
                            reqData += BLINKER_F(",");
                            reqData += STRING_format(digitalRead(set_pin));
                            BProto::serialPrint(reqData);
                            BProto::serialPrint(BLINKER_CMD_OK);
                            return;
                    //     }
                    // }
                }
            }
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_GPIOWREAD;
            reqData += BLINKER_F(":");
            reqData += STRING_format(set_pin);
            reqData += BLINKER_F(",3,");
            reqData += STRING_format(digitalRead(set_pin));
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
            // BProto::serialPrint(BLINKER_CMD_ERROR);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_BLINKER_MQTT) {
            // BProto::serialPrint(BLINKER_CMD_OK);

            BLINKER_LOG(BLINKER_CMD_BLINKER_MQTT);

            blinker_at_state_t at_state = _slaverAT->state();

            BLINKER_LOG(at_state);

            switch (at_state)
            {
                case AT_NONE:
                    // BProto::serialPrint();
                    break;
                case AT_TEST:
                    reqData = BLINKER_CMD_AT;
                    reqData += BLINKER_F("+");
                    reqData += BLINKER_CMD_BLINKER_MQTT;
                    reqData += BLINKER_F("=<MQTT_CONFIG_MODE>,<MQTT_AUTH_KEY>");
                    reqData += BLINKER_F("[,<MQTT_WIFI_SSID>,<MQTT_WIFI_PSWD>]");
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_QUERY:
                    reqData = BLINKER_F("+");
                    reqData += BLINKER_CMD_BLINKER_MQTT;
                    reqData += BLINKER_F(":");
                    reqData += STRING_format(_wlanMode);
                    reqData += BLINKER_F(",");
                    reqData += STRING_format(BProto::authKey());
                    reqData += BLINKER_F(",");
                    reqData += WiFi.SSID();
                    reqData += BLINKER_F(",");
                    reqData += WiFi.psk();
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_SETTING:
                    BLINKER_LOG_ALL(BLINKER_F("MQTT_CONFIG_MODE: "), _slaverAT->getParam(MQTT_CONFIG_MODE));
                    BLINKER_LOG_ALL(BLINKER_F("MQTT_AUTH_KEY: "),  _slaverAT->getParam(MQTT_AUTH_KEY));
                    BLINKER_LOG_ALL(BLINKER_F("MQTT_WIFI_SSID: "), _slaverAT->getParam(MQTT_WIFI_SSID));
                    BLINKER_LOG_ALL(BLINKER_F("MQTT_WIFI_PSWD: "), _slaverAT->getParam(MQTT_WIFI_PSWD));

                    if ((_slaverAT->getParam(MQTT_CONFIG_MODE)).toInt() == BLINKER_CMD_COMCONFIG_NUM)
                    {
                        BLINKER_LOG_ALL(BLINKER_F("BLINKER_CMD_COMWLAN"));

                        if (BLINKER_COMWLAN_PARAM_NUM != _slaverAT->paramNum()) return;

                        if (_status == BL_INITED)
                        {
                            reqData = BLINKER_F("+");
                            reqData += BLINKER_CMD_BLINKER_MQTT;
                            reqData += BLINKER_F(":");
                            reqData += BProto::deviceId();
                            reqData += BLINKER_F(",");
                            reqData += BProto::uuid();
                            BProto::serialPrint(reqData);
                            BProto::serialPrint(BLINKER_CMD_OK);
                            return;
                        }

                        BProto::connectWiFi((_slaverAT->getParam(MQTT_WIFI_SSID)).c_str(), 
                                    (_slaverAT->getParam(MQTT_WIFI_PSWD)).c_str());
                        
                        BProto::begin((_slaverAT->getParam(MQTT_AUTH_KEY)).c_str());
                        _status = BL_INITED;
                        _wlanMode = BLINKER_CMD_COMCONFIG_NUM;
                    }
                    else if ((_slaverAT->getParam(MQTT_CONFIG_MODE)).toInt() == BLINKER_CMD_SMARTCONFIG_NUM)
                    {
                        BLINKER_LOG_ALL(BLINKER_F("BLINKER_CMD_SMARTCONFIG"));

                        if (BLINKER_SMCFG_PARAM_NUM != _slaverAT->paramNum()) return;

                        if (_status == BL_INITED)
                        {
                            reqData = BLINKER_F("+");
                            reqData += BLINKER_CMD_BLINKER_MQTT;
                            reqData += BLINKER_F(":");
                            reqData += BProto::deviceId();
                            reqData += BLINKER_F(",");
                            reqData += BProto::uuid();
                            BProto::serialPrint(reqData);
                            BProto::serialPrint(BLINKER_CMD_OK);
                            return;
                        }

                        if (!BProto::autoInit()) BProto::smartconfig();

                        BProto::begin((_slaverAT->getParam(MQTT_AUTH_KEY)).c_str());
                        _status = BL_INITED;
                        _wlanMode = BLINKER_CMD_SMARTCONFIG_NUM;
                    }
                    else if ((_slaverAT->getParam(MQTT_CONFIG_MODE)).toInt() == BLINKER_CMD_APCONFIG_NUM)
                    {
                        BLINKER_LOG(BLINKER_F("BLINKER_CMD_APCONFIG"));

                        if (BLINKER_APCFG_PARAM_NUM != _slaverAT->paramNum()) return;

                        if (_status == BL_INITED)
                        {
                            reqData = BLINKER_F("+");
                            reqData += BLINKER_CMD_BLINKER_MQTT;
                            reqData += BLINKER_F(":");
                            reqData += BProto::deviceId();
                            reqData += BLINKER_F(",");
                            reqData += BProto::uuid();
                            BProto::serialPrint(reqData);
                            BProto::serialPrint(BLINKER_CMD_OK);
                            return;
                        }

                        if (!BProto::autoInit())
                        {
                            BProto::softAPinit();
                            // while(WiFi.status() != WL_CONNECTED) {
                            //     BProto::serverClient();

                            //     ::delay(10);
                            // }
                        }

                        BProto::begin((_slaverAT->getParam(MQTT_AUTH_KEY)).c_str());
                        _status = BL_INITED;
                        _wlanMode = BLINKER_CMD_APCONFIG_NUM;
                    }
                    else {
                        return;
                    }

                    reqData = BLINKER_F("+");
                    reqData += BLINKER_CMD_BLINKER_MQTT;
                    reqData += BLINKER_F(":");
                    reqData += BProto::deviceId();
                    reqData += BLINKER_F(",");
                    reqData += BProto::uuid();
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_ACTION:
                    // BProto::serialPrint();
                    break;
                default :
                    break;
            }
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_BLINKER_ALIGENIE) {
            // BProto::serialPrint(BLINKER_CMD_OK);

            BLINKER_LOG(BLINKER_CMD_BLINKER_ALIGENIE);

            blinker_at_state_t at_state = _slaverAT->state();

            BLINKER_LOG_ALL(at_state);

            switch (at_state)
            {
                case AT_NONE:
                    // BProto::serialPrint();
                    break;
                case AT_TEST:
                    reqData = BLINKER_CMD_AT;
                    reqData += BLINKER_F("+");
                    reqData += BLINKER_CMD_BLINKER_ALIGENIE;
                    reqData += BLINKER_F("=<type>");
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_QUERY:
                    reqData = BLINKER_F("+");
                    reqData += BLINKER_CMD_BLINKER_ALIGENIE;
                    reqData += BLINKER_F(":");
                    reqData += STRING_format(_aliType);
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_SETTING:
                    BLINKER_LOG_ALL(BLINKER_F("BLINKER_ALIGENIE_CFG_NUM: "), _slaverAT->getParam(BLINKER_ALIGENIE_CFG_NUM));

                    if (BLINKER_ALIGENIE_PARAM_NUM != _slaverAT->paramNum()) return;

                    if ((_slaverAT->getParam(BLINKER_ALIGENIE_CFG_NUM)).toInt() == ALI_LIGHT)
                    {
                        BLINKER_LOG_ALL(BLINKER_F("ALI_LIGHT"));
                        _aliType = ALI_LIGHT;
                    }
                    else if ((_slaverAT->getParam(BLINKER_ALIGENIE_CFG_NUM)).toInt() == ALI_OUTLET)
                    {
                        BLINKER_LOG_ALL(BLINKER_F("ALI_OUTLET"));
                        _aliType = ALI_OUTLET;
                    }
                    else if ((_slaverAT->getParam(BLINKER_ALIGENIE_CFG_NUM)).toInt() == ALI_SENSOR)
                    {
                        BLINKER_LOG_ALL(BLINKER_F("ALI_SENSOR"));
                        _aliType = ALI_SENSOR;
                    }
                    else {
                        BLINKER_LOG_ALL(BLINKER_F("ALI_NONE"));
                        _aliType = ALI_NONE;
                    }
                    BProto::aligenieType(_aliType);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_ACTION:
                    // BProto::serialPrint();
                    break;
                default :
                    break;
            }
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_BLINKER_DUEROS) {
            // BProto::serialPrint(BLINKER_CMD_OK);

            BLINKER_LOG(BLINKER_CMD_BLINKER_DUEROS);

            blinker_at_state_t at_state = _slaverAT->state();

            BLINKER_LOG_ALL(at_state);

            switch (at_state)
            {
                case AT_NONE:
                    // BProto::serialPrint();
                    break;
                case AT_TEST:
                    reqData = BLINKER_CMD_AT;
                    reqData += BLINKER_F("+");
                    reqData += BLINKER_CMD_BLINKER_DUEROS;
                    reqData += BLINKER_F("=<type>");
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_QUERY:
                    reqData = BLINKER_F("+");
                    reqData += BLINKER_CMD_BLINKER_DUEROS;
                    reqData += BLINKER_F(":");
                    reqData += STRING_format(_duerType);
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_SETTING:
                    BLINKER_LOG_ALL(BLINKER_F("BLINKER_DUEROS_CFG_NUM: "), _slaverAT->getParam(BLINKER_ALIGENIE_CFG_NUM));

                    if (BLINKER_DUEROS_PARAM_NUM != _slaverAT->paramNum()) return;

                    if ((_slaverAT->getParam(BLINKER_DUEROS_CFG_NUM)).toInt() == ALI_LIGHT)
                    {
                        BLINKER_LOG_ALL(BLINKER_F("DUER_LIGHT"));
                        _duerType = DUER_LIGHT;
                    }
                    else if ((_slaverAT->getParam(BLINKER_ALIGENIE_CFG_NUM)).toInt() == ALI_OUTLET)
                    {
                        BLINKER_LOG_ALL(BLINKER_F("DUER_OUTLET"));
                        _duerType = DUER_OUTLET;
                    }
                    else if ((_slaverAT->getParam(BLINKER_ALIGENIE_CFG_NUM)).toInt() == ALI_SENSOR)
                    {
                        BLINKER_LOG_ALL(BLINKER_F("DUER_SENSOR"));
                        _duerType = DUER_SENSOR;
                    }
                    else {
                        BLINKER_LOG_ALL(BLINKER_F("DUER_NONE"));
                        _duerType = DUER_NONE;
                    }
                    BProto::duerType(_duerType);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_ACTION:
                    // BProto::serialPrint();
                    break;
                default :
                    break;
            }
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_TIMEZONE) {

            BLINKER_LOG(BLINKER_CMD_TIMEZONE);

            blinker_at_state_t at_state = _slaverAT->state();

            BLINKER_LOG(at_state);

            switch (at_state)
            {
                case AT_NONE:
                    // BProto::serialPrint();
                    break;
                case AT_TEST:
                    reqData = BLINKER_CMD_AT;
                    reqData += BLINKER_F("+");
                    reqData += BLINKER_CMD_TIMEZONE;
                    reqData += BLINKER_F("=<TIMEZONE>");
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_QUERY:
                    reqData = BLINKER_F("+");
                    reqData += BLINKER_CMD_BLINKER_MQTT;
                    reqData += BLINKER_F(":");
                    reqData += STRING_format(getTimezone());
                    BProto::serialPrint(reqData);
                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_SETTING:
                    BLINKER_LOG_ALL(BLINKER_F("BLINKER_TIMEZONE_CFG_NUM: "), _slaverAT->getParam(BLINKER_TIMEZONE_CFG_NUM));

                    if (BLINKER_TIMEZONE_PARAM_NUM != _slaverAT->paramNum()) return;

                    setTimezone((_slaverAT->getParam(BLINKER_TIMEZONE_CFG_NUM)).toFloat());

                    BProto::serialPrint(BLINKER_CMD_OK);
                    break;
                case AT_ACTION:
                    // BProto::serialPrint();
                    break;
                default :
                    break;
            }
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_TIME_AT && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_TIME_AT;
            reqData += BLINKER_F(":");
            reqData += STRING_format(time());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_SECOND && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_SECOND;
            reqData += BLINKER_F(":");
            reqData += STRING_format(second());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_SECOND && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_SECOND;
            reqData += BLINKER_F(":");
            reqData += STRING_format(second());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_MINUTE && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_MINUTE;
            reqData += BLINKER_F(":");
            reqData += STRING_format(minute());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_HOUR && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_HOUR;
            reqData += BLINKER_F(":");
            reqData += STRING_format(hour());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_WDAY && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_WDAY;
            reqData += BLINKER_F(":");
            reqData += STRING_format(wday());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_MDAY && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_MDAY;
            reqData += BLINKER_F(":");
            reqData += STRING_format(mday());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_YDAY && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_YDAY;
            reqData += BLINKER_F(":");
            reqData += STRING_format(yday());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_MONTH && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_MONTH;
            reqData += BLINKER_F(":");
            reqData += STRING_format(month());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_YEAR && _slaverAT->state() == AT_QUERY) {
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_YEAR;
            reqData += BLINKER_F(":");
            reqData += STRING_format(year());
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_WEATHER_AT && _slaverAT->state() == AT_SETTING) {
            if (1 != _slaverAT->paramNum()) return;
            
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_WEATHER_AT;
            reqData += BLINKER_F(":");
            reqData += STRING_format(weather(_slaverAT->getParam(0)));
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_AQI_AT && _slaverAT->state() == AT_SETTING) {
            if (1 != _slaverAT->paramNum()) return;
            
            reqData = BLINKER_F("+");
            reqData += BLINKER_CMD_AQI_AT;
            reqData += BLINKER_F(":");
            reqData += STRING_format(aqi(_slaverAT->getParam(0)));
            
            BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_NOTICE_AT && _slaverAT->state() == AT_SETTING) {
            if (1 != _slaverAT->paramNum()) return;
            
            // reqData = "+" + STRING_format(BLINKER_CMD_NOTICE_AT) + 
            //         ":" + STRING_format(aqi(_slaverAT->getParam(0)));
            notify(_slaverAT->getParam(0));
            // BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
        else if (_slaverAT->cmd() == BLINKER_CMD_SMS_AT && _slaverAT->state() == AT_SETTING) {
            if (1 != _slaverAT->paramNum()) return;
            
            // reqData = "+" + STRING_format(BLINKER_CMD_NOTICE_AT) + 
            //         ":" + STRING_format(aqi(_slaverAT->getParam(0)));
            sms(_slaverAT->getParam(0));
            // BProto::serialPrint(reqData);
            BProto::serialPrint(BLINKER_CMD_OK);
        }
    }
    
    String BlinkerApi::getMode(uint8_t mode)
    {
        switch (mode)
        {
            case BLINKER_CMD_COMCONFIG_NUM :
                return BLINKER_CMD_COMCONFIG;
            case BLINKER_CMD_SMARTCONFIG_NUM :
                return BLINKER_CMD_SMARTCONFIG;
            case BLINKER_CMD_APCONFIG_NUM :
                return BLINKER_CMD_APCONFIG;
            default :
                return BLINKER_CMD_COMCONFIG;
        }
    }    
    
    bool BlinkerApi::serialAvailable()
    {
        if (BProto::serialAvailable())
        {
            _slaverAT = new BlinkerSlaverAT();

            _slaverAT->update(BProto::serialLastRead());
            
            BLINKER_LOG_ALL(BLINKER_F("state: "), _slaverAT->state());
            BLINKER_LOG_ALL(BLINKER_F("cmd: "), _slaverAT->cmd());
            BLINKER_LOG_ALL(BLINKER_F("paramNum: "), _slaverAT->paramNum());

            if (_slaverAT->state())
            {
                parseATdata();

                free(_slaverAT);

                return false;
            }

            free(_slaverAT);

            return true;
        }
        else
        {
            return false;
        }
    }
    
    void BlinkerApi::serialPrint(const String & s)
    {
        BProto::serialPrint(s);
    }
    
    void BlinkerApi::atHeartbeat()
    {
        BProto::serialPrint(BProto::lastRead());
    }
#endif

#if defined(BLINKER_MQTT_AT)
    
    void BlinkerApi::atRespOK(const String & _data, uint32_t timeout)
    {
        bool _isAlive = false;
        uint32_t _now_time = millis();
        while (!_isAlive) {
            BProto::print(_data);
            BProto::printNow();
            // _now_time = millis();

            while((millis() - _now_time) < timeout)
            {
                run();

                if (BProto::available())
                {
                    if (strcmp((BProto::dataParse()), BLINKER_CMD_OK) == 0)
                    {
                        _isAlive = true;
                    }

                    BLINKER_LOG(BLINKER_F("dataParse: "), BProto::dataParse());
                    BLINKER_LOG(BLINKER_F("strlen: "), strlen(BProto::dataParse()));
                    BLINKER_LOG(BLINKER_F("strlen: "), strlen(BLINKER_CMD_OK));
                    BProto::flush();
                }
                // ::delay(10);
            }

            _now_time += timeout;
        }
    }

    
    void BlinkerApi::initCheck(const String & _data, uint32_t timeout)
    {
        BProto::connect();

        atRespOK(BLINKER_CMD_AT);

        #if defined(BLINKER_ALIGENIE_LIGHT)
            atRespOK(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_BLINKER_ALIGENIE + STRING_format("=1"));
        #elif defined(BLINKER_ALIGENIE_OUTLET)
            atRespOK(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_BLINKER_ALIGENIE + STRING_format("=2"));
        #elif defined(BLINKER_ALIGENIE_SENSOR)
            atRespOK(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_BLINKER_ALIGENIE + STRING_format("=3"));
        #endif

        #if defined(BLINKER_DUEROS_LIGHT)
            atRespOK(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_BLINKER_DUEROS + STRING_format("=1"));
        #elif defined(BLINKER_DUEROS_OUTLET)
            atRespOK(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_BLINKER_DUEROS + STRING_format("=2"));
        #elif defined(BLINKER_DUEROS_SENSOR)
            atRespOK(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_BLINKER_DUEROS + STRING_format("=3"));
        #endif

        String cmd_start = BLINKER_CMD_AT + STRING_format("+") + \
                        BLINKER_CMD_BLINKER_MQTT + STRING_format("=");

        #if defined(BLINKER_ESP_SMARTCONFIG)
            cmd_start += "1,";
        #elif defined(BLINKER_APCONFIG)
            cmd_start += "2,";
        #else
            cmd_start += "0,";
        #endif

        cmd_start += _data;

        ::delay(100);

        BProto::print(cmd_start);//cmd_start + _data);
        BProto::printNow();

        bool _isInit = false;
        while (!_isInit) {
            run();

            if (BProto::available())
            {
                // if (!_masterAT) {
                _masterAT = new BlinkerMasterAT();

                _masterAT->update(STRING_format(BProto::dataParse()));
                // }
                // else {
                //     _masterAT->update(STRING_format(BProto::dataParse()));
                // }

                BLINKER_LOG_ALL(BLINKER_F("getState: "), _masterAT->getState());
                BLINKER_LOG_ALL(BLINKER_F("reqName: "), _masterAT->reqName());
                BLINKER_LOG_ALL(BLINKER_F("paramNum: "), _masterAT->paramNum());

                BLINKER_LOG_FreeHeap();

                if (_masterAT->reqName() == BLINKER_CMD_BLINKER_MQTT && 
                    _masterAT->paramNum() == 2)
                {
                    _isInit = true;
                    BLINKER_LOG_ALL("ESP AT init");
                }

                free(_masterAT);
            }
        }
    }

    
    void BlinkerApi::atResp()
    {
        if (strcmp(BProto::dataParse(), BLINKER_CMD_OK) == 0 ||
            strcmp(BProto::dataParse(), BLINKER_CMD_ERROR) == 0)
        {
            _fresh = true;
            // BProto::flushAll();
        }
    }

    
    void BlinkerApi::parseATdata()
    {
        uint32_t at_start = millis();
        while (!BProto::available())
        {
            run();
            if (millis() - at_start > BLINKER_AT_MSG_TIMEOUT) break;
        }

        _masterAT = new BlinkerMasterAT();
        _masterAT->update(STRING_format(BProto::dataParse()));

        BLINKER_LOG_ALL(BLINKER_F("getState: "), _masterAT->getState());
        BLINKER_LOG_ALL(BLINKER_F("reqName: "), _masterAT->reqName());
        BLINKER_LOG_ALL(BLINKER_F("paramNum: "), _masterAT->paramNum());

        BProto::flush();
    }

    
    int BlinkerApi::analogRead()
    {
        BProto::print(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_ADC + "?");
        BProto::printNow();

        parseATdata();

        if (_masterAT->getState() != AT_M_NONE && 
            _masterAT->reqName() == BLINKER_CMD_ADC) {              

            int a_read = _masterAT->getParam(0).toInt();
            free(_masterAT);

            return a_read;
        }
        else {
            free(_masterAT);

            return 0;
        }
    }

    
    void BlinkerApi::pinMode(uint8_t pin, uint8_t mode)
    {
        String pin_data = BLINKER_CMD_AT + STRING_format("+") + \
                            BLINKER_CMD_IOSETCFG + "=" + \
                            STRING_format(pin) + ",";
        switch (mode)
        {
            case INPUT :
                pin_data += "0,0";
                break;
            case OUTPUT :
                pin_data += "1,0";
            break;
            case INPUT_PULLUP :
                pin_data += "0,1";
                break;
            #if defined(ESP8266)
                case INPUT_PULLDOWN_16 :
                    pin_data += "0,2";
                    break;
            #elif defined(ESP32)
                case INPUT_PULLDOWN :
                    pin_data += "0,2";
                    break;
            #endif
            default :
                pin_data += "0,0";
                break;
        }

        // parseATdata();
        // free(_masterAT);
    }

    
    void BlinkerApi::digitalWrite(uint8_t pin, uint8_t val)
    {
        BProto::print(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_GPIOWRITE + "=" + \
                    STRING_format(pin) + "," + \
                    STRING_format(val ? 0 : 1));

        BProto::printNow();

        // parseATdata();
    }

    
    int BlinkerApi::digitalRead(uint8_t pin)
    {
        BProto::print(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_GPIOWREAD + "=" + \
                    STRING_format(pin));

        BProto::printNow();

        parseATdata();
        // free(_masterAT);

        if (_masterAT->getState() != AT_M_NONE && 
            _masterAT->reqName() == BLINKER_CMD_GPIOWREAD) {              

            int d_read = _masterAT->getParam(2).toInt();
            free(_masterAT);

            return d_read;
        }
        else {
            free(_masterAT);

            return 0;
        }
    }

    
    void BlinkerApi::setTimezone(float tz)
    {
        BProto::print(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_TIMEZONE + "=" + \
                    STRING_format(tz));

        BProto::printNow();
    }

    
    float BlinkerApi::getTimezone()
    {
        BProto::print(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_TIMEZONE + "?");

        BProto::printNow();

        parseATdata();

        if (_masterAT->getState() != AT_M_NONE && 
            _masterAT->reqName() == BLINKER_CMD_TIMEZONE) {
            
            float tz_read = _masterAT->getParam(0).toFloat();
            free(_masterAT);

            return tz_read;
        }
        else {
            free(_masterAT);

            return 8.0;
        }
    }

    
    int32_t BlinkerApi::atGetInt(const String & cmd)
    {
        BProto::print(BLINKER_CMD_AT + STRING_format("+") + cmd + "?");

        BProto::printNow();

        parseATdata();

        if (_masterAT->getState() != AT_M_NONE && 
            _masterAT->reqName() == cmd) {
            
            int32_t at_read = _masterAT->getParam(0).toInt();
            free(_masterAT);

            return at_read;
        }
        else {
            free(_masterAT);

            return 0;
        }
    }

    
     template<typename T>
    String BlinkerApi::atGetString(const String & cmd, const T& msg)
    {
        BProto::print(BLINKER_CMD_AT + STRING_format("+") + \
                    cmd + "=" + STRING_format(msg));

        BProto::printNow();

        parseATdata();

        if (_masterAT->getState() != AT_M_NONE && 
            _masterAT->reqName() == cmd) {
            
            String at_read = _masterAT->getParam(0);
            free(_masterAT);

            return at_read;
        }
        else {
            free(_masterAT);

            return 0;
        }
    }

    
    String BlinkerApi::weather(const String & _city)
    {
        return atGetString(BLINKER_CMD_WEATHER_AT, _city);
    }

    
    String BlinkerApi::aqi(const String & _city)
    {
        return atGetString(BLINKER_CMD_AQI_AT, _city);
    }

    
     template<typename T>
    bool BlinkerApi::sms(const T& msg)
    {
        return atGetString(BLINKER_CMD_SMS_AT, msg);
    }

    
    void BlinkerApi::reset()
    {
        BProto::print(BLINKER_CMD_AT + STRING_format("+") + BLINKER_CMD_RST);

        BProto::printNow();
    }
#endif

#if defined(BLINKER_MQTT_AT)
    // void BlinkerApi::freshAlive()
    // {
    //     BProto::freshAlive();
    // }

    void BlinkerApi::atInit(const char* _auth)
    {
        // strcpy(_authKey, _auth);

        initCheck(STRING_format(_auth));
    }

    void BlinkerApi::atInit(const char* _auth, const char* _ssid, const char* _pswd)
    {
        // strcpy(_authKey, _auth);

        String init_data =  STRING_format(_auth) + "," + \
                            STRING_format(_ssid) + "," + \
                            STRING_format(_pswd);

        initCheck(init_data);
    }
#endif

#if defined(BLINKER_PRO)
    #if defined(BLINKER_BUTTON_LONGPRESS_POWERDOWN)
        
        uint16_t BlinkerApi::pressedTime()
        {
            uint32_t _pressedTime = millis() - _startTime;

            if (_isLongPressed)
            {
                if (_pressedTime >= BLINKER_PRESSTIME_RESET) return BLINKER_PRESSTIME_RESET;
                else return _pressedTime;
            }
            else {
                return 0;
            }
        }
    #endif

    
    void BlinkerApi::checkRegister(const JsonObject& data)
    {
        String _type = data[BLINKER_CMD_REGISTER];

        if (_type.length() > 0)
        {
            if (_type == STRING_format(_deviceType))
            {
                _getRegister = true;
                
                BLINKER_LOG_ALL(BLINKER_F("getRegister!"));
                
                print(BLINKER_CMD_MESSAGE, "success");
            }
            else
            {
                BLINKER_LOG_ALL(BLINKER_F("not getRegister!"));
                
                print(BLINKER_CMD_MESSAGE, "deviceType check fail");
            }
            BProto::printNow();
        }
    }

    
    void BlinkerApi::setType(const char* _type)
    {
        _deviceType = _type;

        Bwlan.setType(_type);
        
        BLINKER_LOG_ALL(BLINKER_F("API deviceType: "), _type);
    }

    
    void BlinkerApi::reset()
    {
        BLINKER_LOG(BLINKER_F("Blinker reset..."));
        char _authCheck = 0x00;
        char _uuid[BLINKER_AUUID_SIZE] = {0};
        EEPROM.begin(BLINKER_EEP_SIZE);
        EEPROM.put(BLINKER_EEP_ADDR_AUTH_CHECK, _authCheck);
        EEPROM.put(BLINKER_EEP_ADDR_AUUID, _uuid);
        EEPROM.commit();
        EEPROM.end();
        Bwlan.deleteConfig();
        Bwlan.reset();
        ESP.restart();
    }

    
    void BlinkerApi::tick()
    {
        // Detect the input information
        int buttonLevel = digitalRead(_pin); // current button signal.
        unsigned long now = millis(); // current (relative) time in msecs.

        // Implementation of the state machine
        if (_state == 0) { // waiting for menu pin being pressed.
            if (buttonLevel == _buttonPressed) {
                _state = 1; // step to state 1
                _startTime = now; // remember starting time
            } // if

        } else if (_state == 1) { // waiting for menu pin being released.

            if ((buttonLevel == _buttonReleased) && ((unsigned long)(now - _startTime) < _debounceTicks)) {
                // button was released to quickly so I assume some debouncing.
                // go back to state 0 without calling a function.
                _state = 0;

            } else if (buttonLevel == _buttonReleased) {
                _state = 2; // step to state 2
                _stopTime = now; // remember stopping time

            } else if ((buttonLevel == _buttonPressed) && ((unsigned long)(now - _startTime) > _pressTicks)) {
                _isLongPressed = true;  // Keep track of long press state
                if (_pressFunc) _pressFunc();
                _longPressStart();
                if (_longPressStartFunc) _longPressStartFunc();
                _longPress();
                if (_duringLongPressFunc) _duringLongPressFunc();
                _state = 6; // step to state 6

            } else {
            // wait. Stay in this state.
            } // if

        } else if (_state == 2) { // waiting for menu pin being pressed the second time or timeout.
            // if (_doubleClickFunc == NULL || (unsigned long)(now - _startTime) > _clickTicks) {
            if ((unsigned long)(now - _startTime) > _clickTicks) {
                // this was only a single short click
                _click();
                if (_clickFunc) _clickFunc();
                _state = 0; // restart.

            } else if ((buttonLevel == _buttonPressed) && ((unsigned long)(now - _stopTime) > _debounceTicks)) {
                _state = 3; // step to state 3
                _startTime = now; // remember starting time
            } // if

        } else if (_state == 3) { // waiting for menu pin being released finally.
            // Stay here for at least _debounceTicks because else we might end up in state 1 if the
            // button bounces for too long.
            if (buttonLevel == _buttonReleased && ((unsigned long)(now - _startTime) > _debounceTicks)) {
                // this was a 2 click sequence.
                _doubleClick();
                if (_doubleClickFunc) _doubleClickFunc();
                _state = 0; // restart.
            } // if

        } else if (_state == 6) { // waiting for menu pin being release after long press.
            if (buttonLevel == _buttonReleased) {
                _isLongPressed = false;  // Keep track of long press state
                _longPressStop();
                if(_longPressStopFunc) _longPressStopFunc();
                _state = 0; // restart.
            } else {
                // button is being long pressed
                _isLongPressed = true; // Keep track of long press state
                _longPress();
                if (_duringLongPressFunc) _duringLongPressFunc();
            } // if

        } // if

        // BLINKER_LOG("_state: ", _state);
    }
#endif

#endif