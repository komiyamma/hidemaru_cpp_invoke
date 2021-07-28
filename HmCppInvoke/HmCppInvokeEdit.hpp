/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

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
    // �L�[���͂�����Ȃǂ̗��R�ŏ����𒆒f����ׂ�����Ԃ��܂��B
    using PFNCheckQueueStatus = BOOL(WINAPI*)();
    static PFNCheckQueueStatus Hidemaru_CheckQueueStatus;

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

        operator std::tuple<int, int>();
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

        operator std::tuple<int, int, int, int>();
    };

    ICursorPos getCursorPos();
    IMousePos getMousePos();
};

