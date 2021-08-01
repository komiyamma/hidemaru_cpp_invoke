/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

//-------------------------------------------------------------------------
// dll���g�̃n���h����t�X�p�X�̏��̕ێ�
//-------------------------------------------------------------------------
class TDllBindType {

    //-------------------------------------------------------------------------
    // �������g(����dll)�̃��W���[���C���X�^���X�n���h��
    static HMODULE hModule;

    //-------------------------------------------------------------------------
    // �������g(����dll)�̃t���p�X
    static wchar_t wszSelfModuleFullPath[MAX_PATH];

    // �������g(����dll)�̃f�B���N�g���̃p�X
    static wchar_t wszSelfModuleDirPath[MAX_PATH];

    //-------------------------------------------------------------------------
    // ����dll���G�ۃ}�N������ǂ̂悤�Ȍ`��loaddll���ꂽ�̂��̏��B
    // ���̏�񂪂���΁Adll��������}�N���𔭍s���邱�Ƃ��o����B
    // -1   :loaddll���ő������ꂽ
    // 0    :�ǂ߂Ă��Ȃ��B(�ǂ߂ĂȂ�������dll���s����ĂȂ��̂ŁA����͂��蓾�Ȃ�)
    // 1�ȏ�:���̐��l�ŏG�ۃ}�N����ő�������Ă���B
    //-------------------------------------------------------------------------
public:
    TDllBindType();
private:
    static int iSelfBindedType;
private:
    static HMODULE getCurrentModule();
public:
    static int getDllBindType();
    static BOOL setDllBindType();
    static std::wstring getInvocantString();
    static std::wstring getSelfModuleFullPath();
    static std::wstring getSelfModuleDir();
};
