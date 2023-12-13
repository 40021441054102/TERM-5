//-- Mux 2x1
module mux2x1(i0, i1, sel, f);
    input i0, i1, sel;
    output f;
    and(b, sel, i1);
    not(nsel, sel);
    and(a, i0, nsel);
    or(f, a, b);
endmodule

//-- Mux 4x1
module mux4x1(i0, i1, i2, i3, sel0, sel1, f);
    input i0, i1, i2, i3, sel0, sel1;
    output f;
    wire f1, f2;
    mux2x1 mx0(.i0(i0), .i1(i1), .sel(sel0), .f(f1));
    mux2x1 mx1(.i0(i2), .i1(i3), .sel(sel0), .f(f2));
    mux2x1 mx2(.i0(f1), .i1(f2), .sel(sel1), .f(f));
endmodule

//-- Mux 4x1 8 bit
module mux4x1_8bit(i0, i1, i2, i3, sel0, sel1, f);
    input [7:0] i0, i1, i2, i3;
    input sel0, sel1;
    output [7:0] f;
    //-- Bit with Index of 0 Multiplexer
    mux4x1 m0(.i0(i0[0]), .i1(i1[0]), .i2(i2[0]), .i3(i3[0]), .sel0(sel0), .sel1(sel1), .f(f[0]));
    //-- Bit with Index of 1 Multiplexer
    mux4x1 m1(.i0(i0[1]), .i1(i1[1]), .i2(i2[1]), .i3(i3[1]), .sel0(sel0), .sel1(sel1), .f(f[1]));
    //-- Bit with Index of 2 Multiplexer
    mux4x1 m2(.i0(i0[2]), .i1(i1[2]), .i2(i2[2]), .i3(i3[2]), .sel0(sel0), .sel1(sel1), .f(f[2]));
    //-- Bit with Index of 3 Multiplexer
    mux4x1 m3(.i0(i0[3]), .i1(i1[3]), .i2(i2[3]), .i3(i3[3]), .sel0(sel0), .sel1(sel1), .f(f[3]));
    //-- Bit with Index of 4 Multiplexer
    mux4x1 m4(.i0(i0[4]), .i1(i1[4]), .i2(i2[4]), .i3(i3[4]), .sel0(sel0), .sel1(sel1), .f(f[4]));
    //-- Bit with Index of 5 Multiplexer
    mux4x1 m5(.i0(i0[5]), .i1(i1[5]), .i2(i2[5]), .i3(i3[5]), .sel0(sel0), .sel1(sel1), .f(f[5]));
    //-- Bit with Index of 6 Multiplexer
    mux4x1 m6(.i0(i0[6]), .i1(i1[6]), .i2(i2[6]), .i3(i3[6]), .sel0(sel0), .sel1(sel1), .f(f[6]));
    //-- Bit with Index of 7 Multiplexer
    mux4x1 m7(.i0(i0[7]), .i1(i1[7]), .i2(i2[7]), .i3(i3[7]), .sel0(sel0), .sel1(sel1), .f(f[7]));
endmodule;

//-- Logic Shift Right Module
module LSR(x, f);
    input [7:0] x;
    output [7:0] f;
    //-- Shift Right Logical bit 0
    and(f[0], x[1], x[1]);
    //-- Shift Right Logical bit 1
    and(f[1], x[2], x[2]);
    //-- Shift Right Logical bit 2
    and(f[2], x[3], x[3]);
    //-- Shift Right Logical bit 3
    and(f[3], x[4], x[4]);
    //-- Shift Right Logical bit 4
    and(f[4], x[5], x[5]);
    //-- Shift Right Logical bit 5
    and(f[5], x[6], x[6]);
    //-- Shift Right Logical bit 6
    and(f[6], x[7], x[7]);
    //-- Shift Right Logical bit 7
    and(f[7], 1'b0, 1'b0);
endmodule

//-- Rotate Right Method
module RR(x, f);
    input [7:0] x;
    output [7:0] f;
    //-- Rotate Right bit 0
    and(f[0], x[1], x[1]);
    //-- Rotate Right bit 1
    and(f[1], x[2], x[2]);
    //-- Rotate Right bit 2
    and(f[2], x[3], x[3]);
    //-- Rotate Right bit 3
    and(f[3], x[4], x[4]);
    //-- Rotate Right bit 4
    and(f[4], x[5], x[5]);
    //-- Rotate Right bit 5
    and(f[5], x[6], x[6]);
    //-- Rotate Right bit 6
    and(f[6], x[7], x[7]);
    //-- Rotate Right bit 7
    and(f[7], x[0], x[0]);
endmodule

//-- Rotate Right with Carry Method
module RRC(x, f, cin, cout);
    output [7:0] f;
    input [7:0] x;
    output cout;
    input cin;
    //-- Cout
    and(cout, x[0], x[0]);
    //-- Rotate Right with Carry bit 0
    and(f[0], x[1], x[1]);
    //-- Rotate Right with Carry bit 1
    and(f[1], x[2], x[2]);
    //-- Rotate Right with Carry bit 2
    and(f[2], x[3], x[3]);
    //-- Rotate Right with Carry bit 3
    and(f[3], x[4], x[4]);
    //-- Rotate Right with Carry bit 4
    and(f[4], x[5], x[5]);
    //-- Rotate Right with Carry bit 5
    and(f[5], x[6], x[6]);
    //-- Rotate Right with Carry bit 6
    and(f[6], x[7], x[7]);
    //-- Rotate Right with Carry bit 7
    and(f[7], cin, cin);
endmodule

//-- Arithmetic Shift Right Method
module ASR(x, f);
    input [7:0] x;
    output [7:0] f;
    //-- Shift Right Logical bit 0
    and(f[0], x[1], x[1]);
    //-- Shift Right Logical bit 1
    and(f[1], x[2], x[2]);
    //-- Shift Right Logical bit 2
    and(f[2], x[3], x[3]);
    //-- Shift Right Logical bit 3
    and(f[3], x[4], x[4]);
    //-- Shift Right Logical bit 4
    and(f[4], x[5], x[5]);
    //-- Shift Right Logical bit 5
    and(f[5], x[6], x[6]);
    //-- Shift Right Logical bit 6
    and(f[6], x[7], x[7]);
    //-- Shift Right Logical bit 7
    and(f[7], x[7], x[7]);
endmodule

//-- Shift Right Unit
module SRU_8bit(x, sel0, sel1, cin, cout, f);
    input cin;
    output cout;
    input [7:0] x;
    output [7:0] f;
    input sel0, sel1;
    wire [7:0] method_lsr, method_rr, method_rrc, method_asr;
    LSR __lsr(.x(x), .f(method_lsr));
    RR __rr(.x(x), .f(method_rr));
    RRC __rrc(.x(x), .f(method_rrc), .cin(cin), .cout(cout));
    ASR __asr(.x(x), .f(method_asr));
    mux4x1_8bit select(.i0(method_lsr), .i1(method_rr), .i2(method_rrc), .i3(method_asr), .sel0(sel0), .sel1(sel1), .f(f));
endmodule

//-- Module to Test Multiplexer 4x1 8 bit
module test_SRU_8bit();
    reg [7:0] x;
    reg sel0, sel1, cin;
    wire [7:0] f;
    wire cout;
    SRU_8bit __test(.x(x), .sel0(sel0), .sel1(sel1), .cin(cin), .cout(cout), .f(f));
    initial begin
        $monitor("\033[0;36mx : %b \033[0m|\033[0;36m S0 : %b, S1 : %b \033[0m|\033[0;97m CIN : %b, COUT : %b \033[0m|\033[0;34m FINAL : %b\033[0m",
            x, sel0, sel1, cin, cout, f
        );
        x = 8'b10100111;
        sel0 = 1'b0;
        sel1 = 1'b0;
        cin = 1'b1;
        #10
        x = 8'b10100111;
        sel1 = 1'b1;
        #10
        x = 8'b10100111;
        sel0 = 1'b1;
        sel1 = 1'b0;
        #10
        x = 8'b10100111;
        sel1 = 1'b1;
    end
endmodule
