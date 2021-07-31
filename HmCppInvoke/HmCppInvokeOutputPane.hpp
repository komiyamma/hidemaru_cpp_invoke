/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

class TOutputPane {
    static HMODULE hHmOutputPaneDLL;
    //-------------------------------------------------------------------------
    // �A�E�g�v�b�g�p�l��
    //-------------------------------------------------------------------------
    using PFNHmOutputPane_Output = int(_cdecl*)(HWND hwnd, BYTE*);
    static PFNHmOutputPane_Output HmOutputPane_Output;
    using PFNHmOutputPane_OutputW = int(_cdecl*)(HWND hwnd, wchar_t* message);
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
    /// <summary>
    /// �A�E�g�v�b�g�g�ւ̕�����̏o�́B
    /// ���s����ɂ́u\r\n�v�Ƃ������悤�Ɂu\r�v���K�v�B
    /// </summary>
    /// <returns>���s�Ȃ�false�A�����Ȃ�true</returns>
    bool output(std::wstring message);

    /// <summary>
    /// �A�E�g�v�b�g�g�ɂ��镶����̈ꎞ�ޔ�
    /// </summary>
    /// <returns>���s�Ȃ�false�A�����Ȃ�true</returns>
    bool push();

    /// <summary>
    /// Push�ɂ���Ĉꎞ�ޔ�����������̕���
    /// </summary>
    /// <returns>���s�Ȃ�false�A�����Ȃ�true</returns>
    bool pop();

    /// <summary>
    /// �A�E�g�v�b�g�g�ɂ��镶����̃N���A
    /// </summary>
    /// <returns>���݂̂Ƃ���A���ۂ��w�������l�͕Ԃ��Ă��Ȃ�</returns>
    bool clear();

    /// <summary>
    /// �A�E�g�v�b�g�g�ւ�SendMessage
    /// </summary>
    /// <returns>SendMessage�̕Ԃ�l(LRESULT�^)�Ɠ���</returns>
    THmNumber sendMessage(int command_id);

    /// <summary>
    /// �A�E�g�v�b�g�g�̃x�[�X�ƂȂ�f�B���N�g���̐ݒ�
    /// </summary>
    /// <returns>���s�Ȃ�false�A�����Ȃ�true</returns>
    bool setBaseDir(std::wstring dirpath);

    /// <summary>
    /// �A�E�g�v�b�g�g��WindowHandle
    /// </summary>
    /// <returns>�A�E�g�v�b�g�g��WindowHandle</returns>
    HWND getWindowHandle();
};

