package sintaticanaliser;

import static sintaticanaliser.SlrColumnsEnum.*;

/** Enumeration of lines and itens consts of SlrTable
 * @see SlrTable
 * @author Henrique Colodetti Escanferla GRR20135427
 */
public enum SlrLinesItensEnum {
    E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15, E16,
    E17, E18, E19, E20, E21, E22, E23, E24, E25, E26, E27, E28, E29, E30, E31,
    E32, E33, E34, E35, E36, E37, E38, E39, E40, E41, E42, E43, E44, E45, E46,
    E47, E48, E49, E50, E51, E52, E53, E54, E55, E56, E57, E58, E59, E60, E61,
    E62, E63, E64, E65, E66, E67, E68, E69, E70, E71, E72, E73, E74, E75, E76,
    E77, E78, E79, E80, E81, E82, E83, E84, E85, E86, E87, E88, E89, E90, E91,
    E92, E93, E94, E95, E96, E97, E98, E99, E100, E101, E102, E103, E104, E105,
    E106, E107, E108, E109, E110, E111, R1(PROG.ordinal(), 4),
    R2(DECL_VAR.ordinal(), 4), R3(CONST.ordinal(), 6), R4(FUNCOES.ordinal(), 2),
    R5(FUNCAO.ordinal(), 12), R6(MAIN.ordinal(), 5), R7(CMDS.ordinal(), 2),
    R8(CMDS.ordinal(), 1), R9(CMD.ordinal(), 1), R10(CMD.ordinal(), 1),
    R11(CMD.ordinal(), 1), R12(CMD.ordinal(), 1), R13(CMD.ordinal(), 1),
    R14(CMD.ordinal(), 2), R15(IF.ordinal(), 8), R16(IF.ordinal(), 12),
    R17(WHILE.ordinal(), 8), R18(FOR.ordinal(), 11), R19(ATR.ordinal(), 4),
    R20(ATR.ordinal(), 4), R21(ATR.ordinal(), 4), R22(ATR.ordinal(), 4),
    R23(ATR.ordinal(), 3), R24(ATR.ordinal(), 4), R25(CH_FUNC.ordinal(), 4),
    R26(INCR.ordinal(), 2), R27(ATR_FOR.ordinal(), 3),
    R28(EXPR_MAT.ordinal(), 3), R29(EXPR_MAT.ordinal(), 3),
    R30(EXPR_MAT.ordinal(), 3), R31(EXPR_MAT.ordinal(), 3),
    R32(TESTE.ordinal(), 1), R33(TESTE.ordinal(), 3), R34(EXPR_REL.ordinal(), 3),
    R35(EXPR_REL.ordinal(), 3), R36(EXPR_REL.ordinal(), 3),
    R37(EXPR_REL.ordinal(), 3), R38(DECL_VAR.ordinal(), 0),
    R39(CONST.ordinal(), 0), R40(FUNCOES.ordinal(), 0), ACEITA;

    // uses ordinal as identifier for everyone
    // and as line index in slrTable for E0 -- E111
    private final int redSymb; // whats symbol's column its reducted from55
    private final int pop; // reduction needs to go back pop steps

    private SlrLinesItensEnum() {
            pop = -1; // invalid pop, easily inform errors
            redSymb = -1; // invalid redSymb, easily inform errors
    }
    
    private SlrLinesItensEnum(int redSymb, int pop) {
        this.redSymb = redSymb;
        this.pop = pop;
    }
    
    /**
     * @return the redSymb
     */
    public int getRedSymb() {
        return redSymb;
    }
    
    /**
     * @return the pop
     */
    public int getPop() {
        return pop;
    }
    
}
