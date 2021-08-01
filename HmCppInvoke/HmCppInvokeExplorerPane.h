/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */


//-------------------------------------------------------------------------
// �t�@�C���}�l�[�W���p�l��
//-------------------------------------------------------------------------
class TExplorerPane {
    static HMODULE hHmExplorerPaneDLL;

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

    /// <summary>
    /// �t�@�C���}�l�[�W���g�̃��[�h�̐ݒ�
    /// </summary>
    /// <param name = "mode">�V���ȃ��[�h�l</param>
    /// <returns>���s�Ȃ�false�A�����Ȃ�true</returns>
    bool setMode(int mode);

    /// <summary>
    /// �t�@�C���}�l�[�W���g�̃��[�h�̎擾
    /// </summary>
    /// <returns>���[�h�̒l</returns>
    int getMode();

    /// <summary>
    /// �t�@�C���}�l�[�W���g�Ɏw��̃t�@�C���̃v���W�F�N�g��ǂݍ���
    /// </summary>
    /// <param name = "filepath">�ǂݍ��ݑΏۂ̃v���W�F�N�g�̃t�@�C���̃t���p�X</param>
    /// <returns>���s�Ȃ�false�A�����Ȃ�true</returns>
    bool loadProject(std::wstring filepath);

    /// <summary>
    /// �t�@�C���}�l�[�W���g�̃v���W�F�N�g���w��t�@�C���ɕۑ�
    /// </summary>
    /// <param name = "filepath">�ۑ��Ώۂ̃v���W�F�N�g�̃t�@�C���̃t���p�X</param>
    /// <returns>���s�Ȃ�false�A�����Ȃ�true</returns>
    bool saveProject(std::wstring filepath);

    /// <summary>
    /// �t�@�C���}�l�[�W���g�Ƀv���W�F�N�g��ǂݍ���ł���Ȃ�΁A���̃t�@�C���p�X���擾����
    /// </summary>
    /// <returns>�t�@�C���̃t���p�X�B�ǂݍ���ł��Ȃ���΋󕶎�</returns>
    std::wstring getProject();

    /// <summary>
    /// �t�@�C���}�l�[�W���g�ւ�SendMessage
    /// <para>�u�R�}���h�l�v��https://help.maruo.co.jp/hidemac/html/240_PaneDll.html</para>
    /// </summary>
    /// <param name = "command_id">�R�}���h�l</param>
    /// <returns>SendMessage�̕Ԃ�l(LRESULT�^)�Ɠ���</returns>
    THmNumber sendMessage(int command_id);

    /// <summary>
    /// �t�@�C���}�l�[�W���g��WindowHandle
    /// </summary>
    /// <returns>�t�@�C���}�l�[�W���g��WindowHandle</returns>
    HWND getWindowHandle();

    /// <summary>
    /// �t�@�C���}�l�[�W���g���u�v���W�F�N�g�v�\���̂Ƃ��A�X�V���ꂽ��Ԃł��邩�ǂ�����Ԃ��܂�
    /// </summary>
    /// <returns>�X�V��ԂȂ�1�A����ȊO��0</returns>
    bool getUpdated();
};
