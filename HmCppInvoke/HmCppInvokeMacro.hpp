/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

class TMacro {
    // dll�̒�����G�ۃ}�N�������s����
    using PFNEvalMacro = BOOL(WINAPI*)(const wchar_t* pwsz);
    static PFNEvalMacro Hidemaru_EvalMacro;
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
    IResult doEval(std::wstring expression);

    /// <summary>
    /// �Ώۂ́u�G�ۃ}�N���ϐ����v�̓ǂݍ���
    /// </summary>
    /// <param name = "varname">�ϐ��̃V���{����</param>
    /// <returns>THmMacroVariable�^�̒l�B�����I�ɂ�std::get&lt;THmNumber&gt;��������std::get&lt;wstring&gt;�Œl���擾���邱�ƂɂȂ�B</returns>
    THmMacroVariable getVar(std::wstring varname);

    /// <summary>
    /// �Ώۂ́u�G�ۃ}�N���ϐ����v�ւ̏�������
    /// </summary>
    /// <param name = "varname">�ϐ��̃V���{����</param>
    /// <param name = "value">�������݂̏ꍇ�A�������l</param>
    /// <returns>����̐��ہB���������true�A���s�����false</returns>
    bool setVar(std::wstring varname, THmMacroVariable value);


    class IFunctionResult {
        THmMacroVariable result;
        THmMacroResultError error;
        std::vector<THmMacroVariable> args;
        std::wstring message;
    public:
        THmMacroVariable getResult();
        THmMacroResultError getException();
        std::vector<THmMacroVariable> getArgs();
        std::wstring getMessage();
        IFunctionResult(THmMacroVariable result, std::vector<THmMacroVariable> args, THmMacroResultError error, std::wstring message);
    };

    /// <summary>
    /// �G�ۃ}�N���́u�֐��v�����s
    /// </summary>
    /// <param name = "func_name">�֐���</param>
    /// <param name = "args0">�}�N���֐��ւ̈���1</param>
    /// <param name = "args1">�}�N���֐��ւ̈���2</param>
    /// <param name = "args2">�}�N���֐��ւ̈���3</param>
    /// <param name = "args3">�}�N���֐��ւ̈���4</param>
    /// <param name = "args4">�}�N���֐��ւ̈���5</param>
    /// <param name = "args5">�}�N���֐��ւ̈���6</param>
    /// <param name = "args6">�}�N���֐��ւ̈���7</param>
    /// <param name = "args7">�}�N���֐��ւ̈���8</param>
    /// <param name = "args8">�}�N���֐��ւ̈���9</param>
    /// <param name = "args9">�}�N���֐��ւ̈���10</param>
    IFunctionResult doFunction(std::wstring func_name, THmMacroVariable args0 = nullptr, THmMacroVariable args1 = nullptr, THmMacroVariable args2 = nullptr, THmMacroVariable args3 = nullptr, THmMacroVariable args4 = nullptr, THmMacroVariable args5 = nullptr, THmMacroVariable args6 = nullptr, THmMacroVariable args7 = nullptr, THmMacroVariable args8 = nullptr, THmMacroVariable args9 = nullptr);

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

    /// <summary>
    /// �G�ۃ}�N���̊֐��̂悤�ȁu���ߕ��v�����s
    /// </summary>
    /// <param name = "statement_name">�i�֐��̂悤�ȁj���ߕ���</param>
    /// <param name = "args0">�}�N�����ߕ��ւ̈���1</param>
    /// <param name = "args1">�}�N�����ߕ��ւ̈���2</param>
    /// <param name = "args2">�}�N�����ߕ��ւ̈���3</param>
    /// <param name = "args3">�}�N�����ߕ��ւ̈���4</param>
    /// <param name = "args4">�}�N�����ߕ��ւ̈���5</param>
    /// <param name = "args5">�}�N�����ߕ��ւ̈���6</param>
    /// <param name = "args6">�}�N�����ߕ��ւ̈���7</param>
    /// <param name = "args7">�}�N�����ߕ��ւ̈���8</param>
    /// <param name = "args8">�}�N�����ߕ��ւ̈���9</param>
    /// <param name = "args9">�}�N�����ߕ��ւ̈���10</param>
    IStatementResult doStatement(std::wstring statement_name, THmMacroVariable args0 = nullptr, THmMacroVariable args1 = nullptr, THmMacroVariable args2 = nullptr, THmMacroVariable args3 = nullptr, THmMacroVariable args4 = nullptr, THmMacroVariable args5 = nullptr, THmMacroVariable args6 = nullptr, THmMacroVariable args7 = nullptr, THmMacroVariable args8 = nullptr, THmMacroVariable args9 = nullptr);

private:
    void SetMacroVarAndMakeMacroKeyArray(const std::vector<THmMacroVariable> value_args, std::vector<std::wstring>& varname_list);
    void ClearMacroVarAndUpdateArgs(const std::vector<THmMacroVariable> value_args, const std::vector<std::wstring> varname_list, std::vector<THmMacroVariable>& updated_value_args);
public:
    class TExec {
    public:
        /// <summary>
        /// �u�}�N�������s���Ă��Ȃ����v�ɁA�v���O�������ŁA������ŐV���ȃ}�N�������s�B
        /// <para>�}�N�������s���Ă��Ȃ����̂ݎ��s�\�ȃ��\�b�h�B</para>
        /// </summary>
        IResult doEval(std::wstring expression);

        /// <summary>
        /// �u�}�N�������s���Ă��Ȃ����v�ɁA�v���O�������ŁA�}�N���t�@�C����^���ĐV���ȃ}�N�������s�B
        /// <para>�}�N�������s���Ă��Ȃ����̂ݎ��s�\�ȃ��\�b�h�B</para>
        /// </summary>
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
};

