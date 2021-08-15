/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

/// <summary>
/// dll��֐��̌Ă΂���̃N���X
/// </summary>
class TDllFuncCalledType {
public:
    TDllFuncCalledType();

private:
    using PFNGetDllFuncCalledType = int(WINAPI*)(int n);
    /// <summary>
    /// dll�̌Ă΂ꂩ���A�֐��̌Ă΂��(�Ԃ�l�̗v���^������̗v���^�𔻒�ł���֐�)�B����
    /// <para>n��-1���w�肷��ƁAloaddll�̂������Ԃ��܂��B1�ȏ��loaddll�֐��̕Ԃ�l�Ɠ����ł��B -1�̏ꍇ��loaddll���œǂݍ��܂ꂽDLL�ł��B</para>
    /// </summary>
    static PFNGetDllFuncCalledType Hidemaru_GetDllFuncCalledType;

public:
    /// <summary>
    /// �G�ۂ̃o�[�W������ 8.66�����Ŗ������ƁA���\�b�h���Ȃ��B���̔���̂��߂̃��\�b�h�B
    /// </summary>
    static bool isMissingMethod();

    /// <summary>
    /// ����dll���G�ۃ}�N����̐��l�n���h��(#dll�Ȃ�)�ŉ��ԂɊ��蓖�Ă��Ă��邩�̐��B-1�Ȃ�Aloaddll�֐��ł͂Ȃ��Aloaddll����bind����Ă���B�B
    /// </summary>
    static int getDllBindType();

public:

    enum class DLLFUNCPARAM {
        NOPARAM = 0,        // �ȍ~�̃p�����[�^�Ȃ�
        INT = 0x0100,       // intptr_t�̃p�����[�^
        CHAR_PTR = 0x0200,  // char*�̃p�����[�^
        WCHAR_PTR = 0x0300, // wchar_t*�̃p�����[�^
        DOUBLE = 0x0400     // double�̃p�����[�^
    };

    /// <summary>
    /// arg_n��1���琔�������Ԃ̒l���w�肷��ƁA1���琔���������̌^�̎�ނ��u���l / ������(char*) / Unicode������(wchar_t*) / ���������_���v����Ԃ��܂��B
    /// <para>�p�����[�^(����)�̍ő��64�ł��B</para> 
    /// <para>�ȉ��̒l�̂����ꂩ���Ԃ�܂��B</para>
    /// </summary>
    /// <returns>�uenum��DLLFUNCPARAM�v�l�̂����ꂩ</returns>
    static DLLFUNCPARAM getFuncParamType(int arg_n);

    /// <summary>
    /// �}�N������dll�֐��̌Ăяo���̈����̃^�C�v���X�g�𓾂�
    /// </summary>
    /// <returns>�����̏��Ԓʂ�́uenum��DLLFUNCPARAM�v�l�̃��X�g</returns>
    static std::vector<DLLFUNCPARAM> getFuncParamTypeList();

    enum class DLLFUNCRETURN {
        NOTCALL = 0,        // �Ă΂�Ă��Ȃ�
        INT = 0x0001,       // int��Ԃ��ׂ�(dllfunc�܂���dllfuncw)
        CHAR_PTR = 0x0002,  // char*��Ԃ��ׂ�(dllfuncstr)
        WCHAR_PTR = 0x0003, // WCHAR*��Ԃ��ׂ�(dllfuncstrw)
        DOUBLE = 0x0004     // double��Ԃ��ׂ�(dllfunc�܂���dllfuncw�ŕ��������_�����L��)
    };

    /// <summary>
    /// dllfunc / dllfuncw / dllfuncstr / dllfuncstrw�̂ǂ�ŌĂ΂ꂽ���ɂ���āAreturn�ŕԂ��ׂ��l�������܂��B 
    /// <para>�ȉ��̒l�̂����ꂩ���Ԃ�܂��B</para> 
    /// <para>dllfunc�����Ă΂�Ă���Ƃ��A�ǂ̂悤�ȌĂ΂�������Ă��邩���擾���܂��B</para>
    /// </summary>
    /// <returns>�uenum��DLLFUNCRETURN�v�l�̂����ꂩ</returns>
    static DLLFUNCRETURN getFuncReturnType();

};
