#pragma once

#include <windows.h>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <variant>

#include "HmCppInvokeDllExport.h"


namespace Hidemaru {
#ifdef USE_FLOATMACRO
    using THmMacroNumber = double;
#else
    using THmMacroNumber = long;
#endif
    using THmMacroVariable = std::variant<nullptr_t, THmMacroNumber, std::wstring>;
    using THmMacroResultError = std::variant<nullptr_t, std::exception>;

    using THmMacroScopeMethodPointer = THmMacroNumber (*)(std::wstring message_parameter);

    class THm : public THmDllExport {
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
        // �G�ۂ̃E�B���h�E�n���h��
        using PFNGetCurrentWindowHandle = HWND(WINAPI*)();
        static PFNGetCurrentWindowHandle Hidemaru_GetCurrentWindowHandle;

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
                int lineno;
                int column;
            public:
                int getLineNo();
                int getColumn();
                ICursorPos(int lineno, int column);
            };

            class IMousePos {
                int lineno;
                int column;
                int x;
                int y;
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
                THmMacroResultError getException();
                std::wstring getMessage();
                IResult(int result, THmMacroResultError error, std::wstring message);
            };

            IResult doEval(std::wstring expression);

            THmMacroVariable getVar(std::wstring varname);
            bool setVar(std::wstring varname, THmMacroVariable value);

            class IFunctionResult {
            public:
                THmMacroVariable getResult();
                std::vector<THmMacroVariable> getArgs();
                THmMacroResultError getException();
                std::wstring getMessage();
                IFunctionResult(THmMacroVariable result, std::vector<THmMacroVariable> args, THmMacroResultError error, std::wstring message);
            };

            IFunctionResult doFunction(std::wstring func_name, THmMacroVariable args0 = nullptr, THmMacroVariable args1 = nullptr, THmMacroVariable args2 = nullptr, THmMacroVariable args3 = nullptr, THmMacroVariable args4 = nullptr, THmMacroVariable args5 = nullptr, THmMacroVariable args6 = nullptr, THmMacroVariable args7 = nullptr, THmMacroVariable args8 = nullptr, THmMacroVariable args9 = nullptr);

            class IStatementResult {
            public:
                int getResult();
                std::vector<THmMacroVariable> getArgs();
                THmMacroResultError getException();
                std::wstring getMessage();
                IStatementResult(int result, std::vector<THmMacroVariable> args, THmMacroResultError error, std::wstring message);
            };

            IStatementResult doStatement(std::wstring statement_name, THmMacroVariable args0 = nullptr, THmMacroVariable args1 = nullptr, THmMacroVariable args2 = nullptr, THmMacroVariable args3 = nullptr, THmMacroVariable args4 = nullptr, THmMacroVariable args5 = nullptr, THmMacroVariable args6 = nullptr, THmMacroVariable args7 = nullptr, THmMacroVariable args8 = nullptr, THmMacroVariable args9 = nullptr);

        public:
            class TExec {
            public:
                IResult doEval(std::wstring expression);
                IResult doFile(std::wstring filepath);
                IResult doMethod(std::wstring message_parameter, THmMacroScopeMethodPointer callback_method);
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


    private:
        // ���̌��ʂ̃o�C�g��(vector.data())�� HmOutputPane.dll��Output�֐��ɂȂ���΁AUnicode�ł��Č��ł���
        static std::vector<BYTE> EncodeWStringToOriginalEncodeVector(std::wstring original_string);

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
            using PFNHmExplorerPane_SetMode = int(_cdecl*)(HWND hwnd, int mode);
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
            static void initHandle(HMODULE handle);
        public:
            static int getBindDllType();
            static BOOL setBindDllType();
            static std::wstring getInvocantString();
            static std::wstring getSelfModuleFullPath();
            static std::wstring getSelfModuleDir();
        };

    public:
        void initDllHandle(HMODULE handle);

        std::vector<THmMacroVariable> updateBindInformation(
            THmDllParamVariable arg0 = nullptr,
            THmDllParamVariable arg1 = nullptr,
            THmDllParamVariable arg2 = nullptr,
            THmDllParamVariable arg3 = nullptr,
            THmDllParamVariable arg4 = nullptr,
            THmDllParamVariable arg5 = nullptr,
            THmDllParamVariable arg6 = nullptr,
            THmDllParamVariable arg7 = nullptr,
            THmDllParamVariable arg8 = nullptr
        );
    };

    extern THmMacroVariable TestDynamicVar;
};



extern Hidemaru::THm Hm;


#pragma once


