#pragma once

#include <windows.h>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <any>



namespace Hidemaru {

    using MacroScopeMethodPointer = long (*)(std::wstring message_parameter);

    class THm {
    public:
        THm();
    // Hm ���R�s�[�֎~�ɂ��Ă����B
    private:
        THm(const THm& src) {}
        void operator =(const THm& src);
    private:
        static double hm_version;
        static double QueryFileVersion(wchar_t* path);
    public:
        double getVersion();
    private:
        static HMODULE hHideExeHandle;
    public:
        HWND getWindowHandle();
    private:
        static wchar_t szHidemaruFullPath[MAX_PATH];
    private:
        bool setVersion();

    public:
        // dll�̌Ă΂ꂩ���A�֐��̌Ă΂��(�Ԃ�l�̗v���^������̗v���^�𔻒�ł���֐�)�B����
        using PFNGetDllFuncCalledType = int(WINAPI*)(int n);
        static PFNGetDllFuncCalledType Hidemaru_GetDllFuncCalledType;

        //-------------------------------------------------------------------------
        // n�� - 1���w�肷��ƁAloaddll�̂������Ԃ��܂��B1�ȏ��loaddll�֐��̕Ԃ�l�Ɠ����ł��B - 1�̏ꍇ��loaddll���œǂݍ��܂ꂽDLL�ł��B

        //-------------------------------------------------------------------------
        // n��0���w�肷��ƁAdllfunc / dllfuncw / dllfuncstr / dllfuncstrw�̂ǂ�ŌĂ΂ꂽ���ɂ���āAreturn�ŕԂ��ׂ��l�������܂��B
        // �ȉ��̒l�̂����ꂩ���Ԃ�܂��B
        // dllfunc�����Ă΂�Ă���Ƃ��A�ǂ̂悤�ȌĂ΂�������Ă��邩���擾���܂��B
        enum class DLLFUNCRETURN {
            NOTCALL = 0,       //�Ă΂�Ă��Ȃ�
            INT = 0x0001,  //int��Ԃ��ׂ�(dllfunc�܂���dllfuncw)
            CHAR_PTR = 0x0002,  //char*��Ԃ��ׂ�(dllfuncstr)
            WCHAR_PTR = 0x0003,  //WCHAR*��Ԃ��ׂ�(dllfuncstrw)
            DOUBLE = 0x0004  //double��Ԃ��ׂ�(dllfunc�܂���dllfuncw�ŕ��������_�����L��)
        };

        //-------------------------------------------------------------------------
        //n��1���琔�������Ԃ̒l���w�肷��ƁA1���琔�����p�����[�^�̎�ނ����l / ������ / Unicode������ / ���������_������Ԃ��܂��B
        // �p�����[�^�̍ő��64�ł��B
        // �ȉ��̒l�̂����ꂩ���Ԃ�܂��B
        enum class DLLFUNCPARAM {
            NOPARAM = 0,       //�ȍ~�̃p�����[�^�Ȃ�
            INT = 0x0100,  //int�̃p�����[�^
            CHAR_PTR = 0x0200,  //char*�̃p�����[�^
            WCHAR_PTR = 0x0300,  //WCHAR*�̃p�����[�^
            DOUBLE = 0x0400   //double�̃p�����[�^
        };

        // �G�ۂ̃E�B���h�E�n���h��
        using PFNGetCurrentWindowHandle = HWND(WINAPI*)();
        static PFNGetCurrentWindowHandle Hidemaru_GetCurrentWindowHandle;

        // ���̌��ʂ̃o�C�g��(vector.data())�� HmOutputPane.dll��Output�֐��ɂȂ���΁AUnicode�ł��Č��ł���
        std::vector<BYTE> EncodeWStringToOriginalEncodeVector(std::wstring original_string);

    public:
        class TEdit {
            // ���ݕҏW���̑S�Ẵe�L�X�g�𓾂�
            using PFNGetTotalTextUnicode = HGLOBAL(WINAPI*)(void);
            static PFNGetTotalTextUnicode Hidemaru_GetTotalTextUnicode;
            // ���ݕҏW���̑I���e�L�X�g�𓾂�(�P���I���̂�)
            using PFNGetSelectedTextUnicode = HGLOBAL(WINAPI*)(void);
            static PFNGetSelectedTextUnicode Hidemaru_GetSelectedTextUnicode;
            // ���ݕҏW���̃e�L�X�g�̃J�[�\��������s�̃e�L�X�g�𓾂�
            using PFNGetLineTextUnicode = HGLOBAL(WINAPI*)(int nLineNo);
            static PFNGetLineTextUnicode Hidemaru_GetLineTextUnicode;
            // ���ݕҏW���̃e�L�X�g�̃J�[�\���̈ʒu���擾����B�}�N����column��lineno����(�����ɂ͈قȂ�)
            using PFNGetCursorPosUnicode = BOOL(WINAPI*)(int* pnLineNo, int* pnColumn);
            static PFNGetCursorPosUnicode Hidemaru_GetCursorPosUnicode;
            // ���ݕҏW���̃e�L�X�g�̃}�E�X�̈ʒu�ɑΉ�����J�[�\���̈ʒu���擾����B
            using PFNGetCursorPosUnicodeFromMousePos = BOOL(WINAPI*)(POINT* ppt, int* pnLineNo, int* pnColumn);
            static PFNGetCursorPosUnicodeFromMousePos Hidemaru_GetCursorPosUnicodeFromMousePos;

        public:
            TEdit();
        public:
            std::wstring getFilePath();
            std::wstring getTotalText();
            bool setTotalText(std::wstring text);
            std::wstring getSelectedText();
            bool setSelectedText(std::wstring text);
            std::wstring getLineText();
            bool setLineText(std::wstring text);
            bool isQueueStatus();

        public:
            class ICursorPos {
            public:
                int getLineNo();
                int getColumn();
                ICursorPos(int lineno, int column);
            };

            class IMousePos {
            public:
                int getLineNo();
                int getColumn();
                int getX();
                int getY();
                IMousePos(int lineno, int column, int x, int y);
            };

            ICursorPos getCursorPos();
            IMousePos getMousePos();
        };

    public:
        TEdit Edit;

    public:
        class TMacro {
            // dll�̒�����G�ۃ}�N�������s����
            using PFNEvalMacro = BOOL(WINAPI*)(const wchar_t* pwsz);
            static PFNEvalMacro Hidemaru_EvalMacro;
        public:
            TMacro();
        public:
            bool isExecuting();

        public:
            class IResult {
            public:
                int getResult();
                std::any getException();
                std::wstring getMessage();
                IResult(int result, std::any error, std::wstring message);
            };

            IResult doEval(std::wstring expression);

            std::any getVar(std::wstring varname);
            bool setVar(std::wstring varname, std::any);

            class IFunctionResult {
            public:
                std::any getResult();
                std::vector<std::any> getArgs();
                std::any getException();
                std::wstring getMessage();
                IFunctionResult(std::any result, std::vector<std::any> args, std::any error, std::wstring message);
            };

            IFunctionResult doFunction(std::wstring func_name, std::any args0 = nullptr, std::any args1 = nullptr, std::any args2 = nullptr, std::any args3 = nullptr, std::any args4 = nullptr, std::any args5 = nullptr, std::any args6 = nullptr, std::any args7 = nullptr, std::any args8 = nullptr, std::any args9 = nullptr);

            class IStatementResult {
            public:
                int getResult();
                std::vector<std::any> getArgs();
                std::any getException();
                std::wstring getMessage();
                IStatementResult(int result, std::vector<std::any> args, std::any error, std::wstring message);
            };

            IStatementResult doStatement(std::wstring statement_name, std::any args0 = nullptr, std::any args1 = nullptr, std::any args2 = nullptr, std::any args3 = nullptr, std::any args4 = nullptr, std::any args5 = nullptr, std::any args6 = nullptr, std::any args7 = nullptr, std::any args8 = nullptr, std::any args9 = nullptr);

        public:
            class TExec {
            public:
                IResult doEval(std::wstring expression);
                IResult doFile(std::wstring filepath);
                IResult doMethod(std::wstring message_parameter, MacroScopeMethodPointer callback_method);
            };

            TExec Exec;
        };

    public:
        TMacro Macro;


    public:
        class TFile {
            // ���̃G���R�[�h�ŊJ�����̂����擾����@�\�ƂȂ�B
            using PFNAnalyzeEncoding = int(WINAPI*)(const WCHAR* pwszFileName, DWORD_PTR lParam1, DWORD_PTR lParam2);
            static PFNAnalyzeEncoding Hidemaru_AnalyzeEncoding;

            // �w��̏G�ۂ�encode���w�肵�āA�t�@�C�����e��ǂݍ���
            using PFNLoadFileUnicode = HGLOBAL(WINAPI*)(const WCHAR* pwszFileName, int nEncode, UINT* pcwchOut, DWORD_PTR lParam1, DWORD_PTR lParam2);
            static PFNLoadFileUnicode Hidemaru_LoadFileUnicode;
        public:
            TFile();

            class IEncoding {
            public:
                int getHmEncode();
                int getMsCodePage();
            };

            IEncoding getEncoding();

            class IHidemaruStreamReader {
            public:
                IEncoding getEncoding();
                std::wstring read();
                std::wstring getFilePath();
                void close();
            };

            IHidemaruStreamReader open(std::wstring filepath, int hm_encode = -1);
        };

    public:
        TFile File;


    public:
        class TOutputPane {
            static HMODULE hHmOutputPaneDLL;
            //-------------------------------------------------------------------------
            // �A�E�g�v�b�g�p�l��
            //-------------------------------------------------------------------------
            using PFNHmOutputPane_Output = int(_cdecl*)(HWND hwnd, BYTE*);
            static PFNHmOutputPane_Output HmOutputPane_Output;
            using PFNHmOutputPane_OutputW = int(_cdecl*)(HWND hwnd, wchar_t *message);
            static PFNHmOutputPane_OutputW HmOutputPane_OutputW;
            using PFNHmOutputPane_Push = int(_cdecl*)(HWND hwnd);
            static PFNHmOutputPane_Push HmOutputPane_Push;
            using PFNHmOutputPane_Pop = int(_cdecl*)(HWND hwnd);
            static PFNHmOutputPane_Pop HmOutputPane_Pop;
            using PFNHmOutputPane_GetWindowHandle = HWND(_cdecl*)(HWND hwnd);
            static PFNHmOutputPane_GetWindowHandle HmOutputPane_GetWindowHandle;
            using PFNHmOutputPane_SetBaseDir = int(_cdecl*)(HWND hwnd, BYTE*);
            static PFNHmOutputPane_SetBaseDir HmOutputPane_SetBaseDir;
        public:
            TOutputPane();
        public:
            bool output(std::wstring message);
            bool push();
            bool pop();
            bool clear();
            long sendMessage(int command_id);
            bool setBaseDir(std::wstring dirpath);
            HWND getWindowHandle();
        };

    public:
        TOutputPane OutputPane;

    public:
        class TExplorerPane {
            static HMODULE hHmExplorerPaneDLL;
            //-------------------------------------------------------------------------
            // �t�@�C���}�l�[�W���p�l��
            //-------------------------------------------------------------------------
            using PFNHmExplorerPane_SetMode = int(_cdecl*)(HWND hwnd, intptr_t);
            static PFNHmExplorerPane_SetMode HmExplorerPane_SetMode;
            using PFNHmExplorerPane_GetMode = int(_cdecl*)(HWND hwnd);
            static PFNHmExplorerPane_GetMode HmExplorerPane_GetMode;
            using PFNHmExplorerPane_LoadProject = int(_cdecl*)(HWND hwnd, BYTE*);
            static PFNHmExplorerPane_LoadProject HmExplorerPane_LoadProject;
            using PFNHmExplorerPane_SaveProject = int(_cdecl*)(HWND hwnd, BYTE*);
            static PFNHmExplorerPane_SaveProject HmExplorerPane_SaveProject;
            using PFNHmExplorerPane_GetProject = BYTE * (_cdecl*)(HWND hwnd);
            static PFNHmExplorerPane_GetProject HmExplorerPane_GetProject;
            using PFNHmExplorerPane_GetWindowHandle = HWND(_cdecl*)(HWND hwnd);
            static PFNHmExplorerPane_GetWindowHandle HmExplorerPane_GetWindowHandle;
            using PFNHmExplorerPane_GetUpdated = int(_cdecl*)(HWND hwnd);
            static PFNHmExplorerPane_GetUpdated HmExplorerPane_GetUpdated;
            using PFNHmExplorerPane_GetCurrentDir = BYTE * (_cdecl*)(HWND hwnd);
            static PFNHmExplorerPane_GetCurrentDir HmExplorerPane_GetCurrentDir;
        public:
            TExplorerPane();
        public:
            bool setMode(int mode);
            int getMode();
            bool loadProject(std::wstring filepath);
            bool saveProject(std::wstring filepath);
            std::wstring getProject();
            long sendMessage(int command_id);
            HWND getWindowHandle();
            bool getUpdated();
        };

    public:
        TExplorerPane ExplorerPane;

        //-------------------------------------------------------------------------
        // dll���g�̃n���h����t�X�p�X�̏��̕ێ�
        //-------------------------------------------------------------------------
    private:
        class SelfDllInfo {

            //-------------------------------------------------------------------------
            // �������g(hmPerl.dll)�̃��W���[���C���X�^���X�n���h��
            static HMODULE hModule;

            //-------------------------------------------------------------------------
            // �������g(hmPerl.dll)�̃t���p�X
            static wchar_t szSelfModuleFullPath[MAX_PATH];

            static wchar_t szSelfModuleDirPath[MAX_PATH];

            //-------------------------------------------------------------------------
            // ����dll���G�ۃ}�N������ǂ̂悤�Ȍ`��loaddll���ꂽ�̂��̏��B
            // ���̏�񂪂���΁Adll��������}�N���𔭍s���邱�Ƃ��o����B
            // -1   :loaddll���ő������ꂽ
            // 0    :�ǂ߂Ă��Ȃ��B(�ǂ߂ĂȂ�������dll���s����ĂȂ��̂ŁA����͂��蓾�Ȃ�)
            // 1�ȏ�:���̐��l�ŏG�ۃ}�N����ő�������Ă���B
            //-------------------------------------------------------------------------
        private:
            static int iSelfBindedType;
        public:
            static void InitializeHandle(HMODULE handle);
        private:
            static int GetBindDllType();
            static BOOL SetBindDllHandle();
            static std::wstring GetInvocantString();
            static std::wstring GetSelfModuleFullPath();
            static std::wstring GetSelfModuleDir();
        };

        public:
            void InitializeSelfDllHandle(HMODULE handle) {
                SelfDllInfo::InitializeHandle(handle);
            }
    };

    extern std::any TestDynamicVar;
};



extern Hidemaru::THm Hm;


#pragma once


