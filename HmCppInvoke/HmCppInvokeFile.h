/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

 /// <summary>
 /// �t�@�C���֘A
 /// </summary>
class TFile {
    // ���̃G���R�[�h�ŊJ�����̂����擾����@�\�ƂȂ�B
    using PFNAnalyzeEncoding = int(WINAPI*)(const WCHAR* pwszFileName, DWORD_PTR lParam1, DWORD_PTR lParam2);
    static PFNAnalyzeEncoding Hidemaru_AnalyzeEncoding;

    // �w��̏G�ۂ�encode���w�肵�āA�t�@�C�����e��ǂݍ���
    using PFNLoadFileUnicode = HGLOBAL(WINAPI*)(const WCHAR* pwszFileName, int nEncode, UINT* pcwchOut, DWORD_PTR lParam1, DWORD_PTR lParam2);
    static PFNLoadFileUnicode Hidemaru_LoadFileUnicode;
public:
    TFile();

    /// <summary>
    /// MsCodePage �� HmEncode ���ꊇ�ň������߂̃N���X
    /// </summary>
    class IEncoding {
        int hm_encode;
        int ms_codepage;
    public:
        IEncoding(int hm_encode, int ms_codepage);
        IEncoding() = default;
        IEncoding(const IEncoding&) = default;

        /// <summary>
        /// �G�ۂ�encode�l�����𓾂�B�����ɂ� �}�N����encode�l �u&amp;  0x3F�v��AND�r�b�g���Z�����l�j
        /// <para>https://help.maruo.co.jp/hidemac/html/060_Keyword_State.html#encode ��0�`28�Ɠ���</para>
        /// </summary>
        int getHmEncode();

        /// <summary>
        /// �}�C�N���\�t�g��CodePage�l�����𓾂�B
        /// <para>Win32api���g���ĕ����G���R�[�h����������ɂ͂��̒l���K�v�ƂȂ邾�낤�B</para>
        /// </summary>
        int getMsCodePage();
    };

    /// <summary>
    /// �G�ۂ�Encode�l����MsCodePage�̒l�𓾂邽�߂̃��\�b�h
    /// �G�ۂ�encode�l�Ƃ́A�����ɂ� �}�N����encode�l �u&amp; 0x3F�v��AND�r�b�g���Z�����l�j
    /// <para>https://help.maruo.co.jp/hidemac/html/060_Keyword_State.html#encode ��0�`28�Ɠ���</para>
    /// </summary>
    /// <param name = "hm_encode">�G�ۂ�Encode�l</param>
    /// <returns>IEncoding�^�̃I�u�W�F�N�g�BMsCodePage �� HmEncode �𓾂���B</returns>
    IEncoding getEncoding(int hm_encode);

    /// <summary>
    /// �w��̃t�@�C���̐�΃p�X����IEncoding�^�I�u�W�F�N�𓾂邽�߂̃��\�b�h
    /// <para>�i���Ȃ��̏G�ۂ̃t�@�C���̃G���R�[�h���f�̐ݒ�ɏ]���B�ėp�I�ȃt�@�C���G���R�[�h����֐��ł͂Ȃ��j</para>
    /// </summary>
    /// <returns>IEncoding�^�̃I�u�W�F�N�g�BMsCodePage �� HmEncode �𓾂���B</returns>
    IEncoding getEncoding(std::wstring filepath);
    const std::map<int, int> getEncodingMap();

    class IHidemaruStreamReader {
        IEncoding encoding;
        std::wstring filepath;
    public:
        IHidemaruStreamReader(std::wstring filepath, IEncoding encoding);
        ~IHidemaruStreamReader();

        /// <summary>
        /// �ΏۂƂȂ��Ă���t�@�C����IEncoding�𓾂�B�G�ۃx�[�X��encoding�l�ƃ}�C�N���\�t�g�x�[�X��CodePage�l�𓾂邱�Ƃ��o����B
        /// </summary>
        IEncoding getEncoding();

        /// <summary>
        /// �ΏۂƂȂ��Ă���t�@�C���̃e�L�X�g���e���ꊇ�œǂݍ��ށB
        /// </summary>
        std::wstring read();

        /// <summary>
        /// �ΏۂƂȂ��Ă���t�@�C���̐�΃p�X�̎擾�B
        /// </summary>
        std::wstring getFilePath();

        /// <summary>
        /// ���݂Ђ炢�Ă���A���� IHidemaruStreamReader �I�u�W�F�N�g�����B
        /// </summary>
        void close();
    };

    /// <summary>
    /// �G�ۂŃt�@�C���̃G���R�[�h�𔻒f���A���̔��f���ʂɊ�Â��ăt�@�C���̃e�L�X�g���e���擾����B
    /// �i�G�ۂɐݒ肳��Ă�����e�ɏ]���j
    /// </summary>
    /// <param name = "filepath">�ǂݍ��ݑΏۂ̃t�@�C���̃p�X</param>
    /// <param name = "hm_encode">�G���R�[�h(�G�ۃ}�N���́uencode�v�̒l)���������Ă���Ȃ�Ύw�肷��A�w�肵�Ȃ��ꍇ�G��API�̎�������ɔC����B</param>
    /// <returns>IHidemaruStreamReader�^�̃I�u�W�F�N�g�B</returns>
    IHidemaruStreamReader open(std::wstring filepath, int hm_encode = -1);
};

