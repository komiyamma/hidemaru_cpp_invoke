/*
 * Copyright (c) 2021-2022 Akitsugu Komiyama
 * under the MIT License
 */

 /// <summary>
 /// �}�N���֘A
 /// </summary>
class TMacro {
    // dll�̒�����G�ۃ}�N�������s����
    using PFNEvalMacro = BOOL(WINAPI*)(const wchar_t* pwsz);
    static PFNEvalMacro Hidemaru_EvalMacro;

    using PFNGetStaticVariable = HGLOBAL(WINAPI*)(const wchar_t* pwszName, int sharedFlag);
    static PFNGetStaticVariable Hidemaru_GetStaticVariable;

    using PFNSetStaticVariable = BOOL(WINAPI*)(const wchar_t* pwszName, const wchar_t* pwszValue, int sharedFlag);
    static PFNSetStaticVariable Hidemaru_SetStaticVariable;
public:
    TMacro();
public:
    /// <summary>
    /// �}�N�������s�����ۂ��𔻒肷��
    /// </summary>
    /// <returns>���s���Ȃ�true, �����łȂ����false</returns>
    bool isExecuting();

public:
    /// <summary>
    /// �}�N�����v���O������������s�����ۂ̕Ԃ�l�̃C���^�[�t�F�C�X
    /// </summary>
    class IResult {
        THmNumber result;
        THmMacroResultError error;
        std::wstring message;
    public:

        /// <summary>
        /// �}�N�����s�����ہB
        /// </summary>
        /// <returns>�}�N�����s�����������ꍇ�ɂ́A1�ȏ�A���s�����ꍇ�ɂ�0�ȉ��̒l�B-1�ȉ��̂��Ƃ����邽��0�Ō��ߑł����Ȃ����ƁB</returns>
        THmNumber getResult();

        /// <summary>
        /// �}�N�����s�̎��s���̗�O�B
        /// </summary>
        /// <returns>�}�N�����s�����s���Ă���ꍇ��exception�^�̗�O�������Ă���B��O���Ȃ���΁Astd::nullopt�������Ă���B</returns>
        THmMacroResultError getException();

        /// <summary>
        /// �}�N�����s���ʂƂ��Ẵ��b�Z�[�W�B���\�b�h�ɂ���ĈقȂ�B
        /// </summary>
        std::wstring getMessage();

        IResult(THmNumber result, THmMacroResultError error, std::wstring message);
    };

    /// <summary>
    /// ���݂́u�}�N�����s���v�ɁA�v���O�������ŁA�}�N���𕶎���Ŏ��s�B
    /// <para>�}�N�����s���̂ݎ��s�\�ȃ��\�b�h</para>
    /// </summary>
    /// <param name = "expression">�}�N�����e�̕�����</param>
    IResult doEval(std::wstring expression);

    /// <summary>
    /// �Ώۂ́u�G�ۃ}�N���ϐ����v�̓ǂݍ���
    /// </summary>
    /// <param name = "varname">�ϐ��̃V���{����</param>
    /// <returns>THmMacroVariable�^�̒l�B�����I�ɂ�std::get&lt;THmNumber&gt;��������std::get&lt;wstring&gt;�Œl���擾���邱�ƂɂȂ�B</returns>
    THmMacroVariable getVar(std::wstring varname);

    /// <summary>
    /// �Ώۂ́u�G�ۃ}�N���ϐ����v�̓ǂݍ��݁B�e���v���[�g�p�����[�^�Ƃ��Č^���w�肷�邱�ƂŃ}�j���A���ł̒l�̎擾���ȗ��ł���B
    /// �e���v���[�g�p�����[�^�Ɏw��\�Ȍ^�́uTHmNumber�v�������́uwstring�v�̂݁B
    /// </summary>
    /// <param name = "varname">�ϐ��̃V���{����</param>
    /// <param name = "T">T�Ɏw��\�Ȍ^�́uTHmNumber�v�������́uwstring�v�̂�</param>
    /// <returns>T�Ŏw�肵���^�̒l�BT�ɂ́uTHmNumber�v�������́uwstring�v�l���w�肵�Ď擾���邱�ƂɂȂ�B</returns>
    template<class T>
    T getVar(std::wstring varname) {
        THmMacroVariable v = getVar(varname);
        T r = std::get<T>(v);
        return r;
    }

    /// <summary>
    /// �Ώۂ́u�G�ۃ}�N���ϐ����v�ւ̏�������
    /// </summary>
    /// <param name = "varname">�ϐ��̃V���{����</param>
    /// <param name = "value">�������݂̏ꍇ�A�������l</param>
    /// <returns>����̐��ہB���������true�A���s�����false</returns>
    bool setVar(std::wstring varname, THmMacroVariable value);


    /// <summary>
    /// �Ώۂ́u�G�ۃ}�N���̐ÓI�ȕϐ����v�ւ̏������� (�G�ۃ}�N����setstaticvariable���������펞���s��)
    /// </summary>
    /// <param name = "varname">�ÓI�ȕϐ��̃V���{����</param>
    /// <param name = "value">������镶����</param>
    /// <param name = "shared_flag">���p�t���O</param>
    /// <returns>����̐��ہB���������true�A���s�����false</returns>
    bool setStaticVar(std::wstring varname, std::wstring value, int shared_flag);

    /// <summary>
    /// �Ώۂ́u�G�ۃ}�N���̐ÓI�ȕϐ����v�̓ǂݍ��� (�G�ۃ}�N����getstaticvariable���������펞���s��)
    /// </summary>
    /// <param name = "varname">�ÓI�ȕϐ��̃V���{����</param>
    /// <param name = "shared_flag">���p�t���O</param>
    /// <returns>�Ώۂ̃L�[�Ɋi�[���ꂽ������^�̒l�B</returns>
    std::wstring getStaticVar(std::wstring varname, int shared_flag);


    class IFunctionResult {
        THmMacroVariable result;
        THmMacroResultError error;
        std::vector<THmMacroVariable> args;
        std::wstring message;
    public:
        THmMacroVariable getResult();
        template<class T>
        T getResult() {
            THmMacroVariable v = getResult();
            T r = std::get<T>(v);
            return r;
        }
        THmMacroResultError getException();
        std::vector<THmMacroVariable> getArgs();
        std::wstring getMessage();
        IFunctionResult(THmMacroVariable result, std::vector<THmMacroVariable> args, THmMacroResultError error, std::wstring message);
    };

private:
    IFunctionResult doFunctionHelper(std::wstring func_name, std::vector<THmMacroVariable> value_args);

public:

    /// <summary>
    /// �G�ۃ}�N���́u�֐��v�����s
    /// </summary>
    /// <param name = "func_name">�֐���</param>
    /// <param name = "args">�}�N���֐��ւ̉ψ���</param>
    template<class... THmMacroFunctionPARAMS>
    IFunctionResult doFunction(std::wstring func_name, THmMacroFunctionPARAMS... args) {

        std::vector<THmMacroVariable> value_args;
        for (THmMacroVariable arg : std::initializer_list<THmMacroVariable>{ args... }) {
            try {
                value_args.push_back(arg);
            }
            catch (...) {
            }
        }

        return doFunctionHelper(func_name, value_args);
    }

    class IStatementResult {
        THmNumber result;
        THmMacroResultError error;
        std::vector<THmMacroVariable> args;
        std::wstring message;
    public:
        THmNumber getResult();
        THmMacroResultError getException();
        std::vector<THmMacroVariable> getArgs();
        std::wstring getMessage();
        IStatementResult(THmNumber result, std::vector<THmMacroVariable> args, THmMacroResultError error, std::wstring message);
    };


private:
    IStatementResult doStatementHelper(std::wstring statement_name, std::vector<THmMacroVariable> value_args);

public:
    /// <summary>
    /// �G�ۃ}�N���̊֐��̂悤�ȁu���ߕ��v�����s
    /// </summary>
    /// <param name = "statement_name">�i�֐��̂悤�ȁj���ߕ���</param>
    /// <param name = "args">�}�N�����ߕ��ւ̉ψ���</param>
    template<class... THmMacroStatementPARAMS>
    IStatementResult doStatement(std::wstring statement_name, THmMacroStatementPARAMS... args) {

        std::vector<THmMacroVariable> value_args;
        for (THmMacroVariable arg : std::initializer_list<THmMacroVariable>{ args... }) {
            try {
                value_args.push_back(arg);
            }
            catch (...) {
            }
        }

        return doStatementHelper(statement_name, value_args);
    }


private:
    void setMacroVarAndMakeMacroKeyArray(const std::vector<THmMacroVariable> value_args, std::vector<std::wstring>& varname_list);
    void clearMacroVarAndUpdateArgs(const std::vector<THmMacroVariable> value_args, const std::vector<std::wstring> varname_list, std::vector<THmMacroVariable>& updated_value_args);
public:
    class TExec {
    public:
        /// <summary>
        /// �u�}�N�������s���Ă��Ȃ����v�ɁA�v���O�������ŁA������ŐV���ȃ}�N�������s�B
        /// <para>�}�N�������s���Ă��Ȃ����̂ݎ��s�\�ȃ��\�b�h�B</para>
        /// </summary>
        /// <param name = "expression">�}�N�����e�̕�����</param>
        IResult doEval(std::wstring expression);

        /// <summary>
        /// �u�}�N�������s���Ă��Ȃ����v�ɁA�v���O�������ŁA�}�N���t�@�C����^���ĐV���ȃ}�N�������s�B
        /// <para>�}�N�������s���Ă��Ȃ����̂ݎ��s�\�ȃ��\�b�h�B</para>
        /// </summary>
        /// <param name = "filepath">�}�N���t�@�C���̃t���p�X</param>
        IResult doFile(std::wstring filepath);

        /// <summary>
        /// �w��̃��[�U�[��`��static���\�b�h���u�V���ȃ}�N�����s��ԁv�Ƃ��ČĂяo��
        /// </summary>
        /// <param name = "message_parameter">������p�����[�^</param>
        /// <param name = "delegate_method">�Ăяo�������֐��������̓��\�b�h�uTHmNumber methodname(wstring message_parameter)�̌^�v�ɏ]�����\�b�h�ł��邱��</param>
        IResult doMethod(std::wstring message_parameter, THmMacroDoMethodType delegate_method);
    };

    /// <summary>
    /// �u�}�N�������s����Ă��Ȃ�������ŁA���߂ă}�N�������s�ł���v�n�̃��\�b�h�Q���̃N���X�ɂ���B���O��Ԃ̑�ցB
    /// </summary>
    TExec Exec;

public:
    /// <summary>
    /// �G�ۃ}�N���ŗp���������̊֐��ł̂ݎg�p�\�ȃt���O�l�B��Ɍ����E�u���EGrep�n�A�����ăG���R�[�h�n�B
    /// </summary>
    class TFlags {
    public:

        /// <summary>
        /// openfile����encode����
        /// </summary>
        class TEncode {
        public:
            static const int sjis = 0x01;
            static const int utf16 = 0x02;
            static const int euc = 0x03;
            static const int jis = 0x04;
            static const int utf7 = 0x05;
            static const int utf8 = 0x06;
            static const int utf16_be = 0x07;
            static const int euro = 0x08;
            static const int gb2312 = 0x09;
            static const int big5 = 0x0a;
            static const int euckr = 0x0b;
            static const int johab = 0x0c;
            static const int easteuro = 0x0d;
            static const int baltic = 0x0e;
            static const int greek = 0x0f;
            static const int russian = 0x10;
            static const int symbol = 0x11;
            static const int turkish = 0x12;
            static const int hebrew = 0x13;
            static const int arabic = 0x14;
            static const int thai = 0x15;
            static const int vietnamese = 0x16;
            static const int mac = 0x17;
            static const int oem = 0x18;
            static const int default = 0x19;
            static const int utf32 = 0x1b;
            static const int utf32_be = 0x1c;
            static const int binary = 0x1a;
            static const int lf = 0x40;
            static const int cr = 0x80;

            //SAVEAS�̑��̃I�v�V�����̐��l�w��
            static const int bom = 0x0600;
            static const int nobom = 0x0400;
            static const int selection = 0x2000;

            //openfile�̑��̃I�v�V�����̐��l�w��
            static const int noaddhist = 0x0100;
            static const int ws = 0x0800;
            static const int wb = 0x1000;
        };

        TEncode Encode;

        class TSearchOption {
        public:
            //searchoption(�����֌W)
            static const int word = 0x00000001;
            static const int casesense = 0x00000002;
            static const int nocasesense = 0x00000000;
            static const int regular = 0x00000010;
            static const int noregular = 0x00000000;
            static const int fuzzy = 0x00000020;
            static const int hilight = 0x00003800;
            static const int nohilight = 0x00002000;
            static const int linknext = 0x00000080;
            static const int loop = 0x01000000;

            //searchoption(�}�X�N�֌W)
            static const int maskcomment = 0x00020000;
            static const int maskifdef = 0x00040000;
            static const int masknormal = 0x00010000;
            static const int maskscript = 0x00080000;
            static const int maskstring = 0x00100000;
            static const int masktag = 0x00200000;
            static const int maskonly = 0x00400000;
            static const int fEnableMaskFlags = 0x00800000;

            //searchoption(�u���֌W)
            static const int fEnableReplace = 0x00000004;
            static const int ask = 0x00000008;
            static const int noclose = 0x02000000;

            //searchoption(grep�֌W)
            static const int subdir = 0x00000100;
            static const int icon = 0x00000200;
            static const int filelist = 0x00000040;
            static const int fullpath = 0x00000400;
            static const int outputsingle = 0x10000000;
            static const int outputsametab = 0x20000000;

            //searchoption(grep���Ēu���֌W)
            static const int backup = 0x04000000;
            static const int preview = 0x08000000;

            // searchoption2���g����A�Ƃ����t���O�B�Ȃ�ƁAint32_max�𒴂��Ă���̂ŁA����ȏ������K�v�B
            const thmnumber fEnableSearchOption2 = (thmnumber)0x80000000;

        };

        TSearchOption SearchOption;

        class TSearchOption2 {
        public:
            //searchoption2
            static const int unmatch = 0x00000001;
            static const int incolormarker = 0x00000002;
            static const int fGrepFormColumn = 0x00000008;
            static const int fGrepFormHitOnly = 0x00000010;
            static const int fGrepFormSortDate = 0x00000020;
        };

        TSearchOption2 SearchOption2;
    };

    TFlags Flags;
};

