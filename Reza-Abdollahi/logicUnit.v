//-- AND 8 bit
module AND_8bit(
    x, y, f
);
    input [7:0] x, y;
    output [7:0] f;
    and(f[0], x[0], y[0]);
    and(f[1], x[1], y[1]);
    and(f[2], x[2], y[2]);
    and(f[3], x[3], y[3]);
    and(f[4], x[4], y[4]);
    and(f[5], x[5], y[5]);
    and(f[6], x[6], y[6]);
    and(f[7], x[7], y[7]);
endmodule

//-- OR 8 bit
module AND_8bit(
    x, y, f
);
    input [7:0] x, y;
    output [7:0] f;
    or(f[0], x[0], y[0]);
    or(f[1], x[1], y[1]);
    or(f[2], x[2], y[2]);
    or(f[3], x[3], y[3]);
    or(f[4], x[4], y[4]);
    or(f[5], x[5], y[5]);
    or(f[6], x[6], y[6]);
    or(f[7], x[7], y[7]);
endmodule

//-- XOR 8 bit
module XOR_8bit(
    x, y, f
);
    input [7:0] x, y;
    output [7:0] f;
    xor(f[0], x[0], y[0]);
    xor(f[1], x[1], y[1]);
    xor(f[2], x[2], y[2]);
    xor(f[3], x[3], y[3]);
    xor(f[4], x[4], y[4]);
    xor(f[5], x[5], y[5]);
    xor(f[6], x[6], y[6]);
    xor(f[7], x[7], y[7]);
endmodule

//-- NOT 8 bit
module NOT_8bit(
    x, f
);
    input [7:0] x;
    output [7:0] f;
    not(f[0], x[0]);
    not(f[1], x[1]);
    not(f[2], x[2]);
    not(f[3], x[3]);
    not(f[4], x[4]);
    not(f[5], x[5]);
    not(f[6], x[6]);
    not(f[7], x[7]);
endmodule

//-- Mux 2x1
module mux2x1(
    i0, i1, sel, f
);
    input i0, i1, sel;
    output f;
    and(a, i0, nsel);
    and(b, i1, sel);
    not(nsel, sel);
    or(f, a, b);
endmodule

//-- Mux 4x1
module mux4x1(
    i0, i1, i2, i3, sel0, sel1, f
);
    input i0, i1, i2, i3, sel0, sel1;
    output f;
    wire f1, f2;
    mux2x1 m1(.i0(i0), .i1(i1), .sel(sel0), .f(f1));
    mux2x1 m2(.i0(i2), .i1(i3), .sel(sel0), .f(f2));
    mux2x1 m3(.i0(f1), .i1(f2), .sel(sel1), .f(f));
endmodule

//-- Mux 4x1 8 bit
module mux4x1_8bit(
    i0, i1, i2, i3, sel0, sel1, f
);
    input [7:0] i0, i1, i2, i3;
    input sel0, sel1;
    output [7:0] f;
    mux4x1 m0(.i0(i0[0]), .i1(i1[0]), .i2(i2[0]), .i3(i3[0]), .sel0(sel0), .sel1(sel1), .f(f[0]));
    mux4x1 m1(.i0(i0[1]), .i1(i1[1]), .i2(i2[1]), .i3(i3[1]), .sel0(sel0), .sel1(sel1), .f(f[1]));
    mux4x1 m2(.i0(i0[2]), .i1(i1[2]), .i2(i2[2]), .i3(i3[2]), .sel0(sel0), .sel1(sel1), .f(f[2]));
    mux4x1 m3(.i0(i0[3]), .i1(i1[3]), .i2(i2[3]), .i3(i3[3]), .sel0(sel0), .sel1(sel1), .f(f[3]));
    mux4x1 m4(.i0(i0[4]), .i1(i1[4]), .i2(i2[4]), .i3(i3[4]), .sel0(sel0), .sel1(sel1), .f(f[4]));
    mux4x1 m5(.i0(i0[5]), .i1(i1[5]), .i2(i2[5]), .i3(i3[5]), .sel0(sel0), .sel1(sel1), .f(f[5]));
    mux4x1 m6(.i0(i0[6]), .i1(i1[6]), .i2(i2[6]), .i3(i3[6]), .sel0(sel0), .sel1(sel1), .f(f[6]));
    mux4x1 m7(.i0(i0[7]), .i1(i1[7]), .i2(i2[7]), .i3(i3[7]), .sel0(sel0), .sel1(sel1), .f(f[7]));
endmodule

//-- Logic Unit 8 bit
module logicUnit_8bit(
    x, y, sel0, sel1, f
);
    input [7:0] x, y;
    input sel0, sel1;
    output [7:0] f;
    wire [7:0] and_x_y, or_x_y, xor_x_y, not_x_y;
    AND_8bit a(.x(x), .y(y), .f(and_x_y));
    OR_8bit o(.x(x), .y(y), .f(or_x_y));
    XOR_8bit x(.x(x), .y(y), .f(xor_x_y));
    NOT_8bit n(.x(x), .f(not_x_y));
    mux4x1_8bit select(.i0(and_x_y), .i1(or_x_y), .i2(xor_x_y), .i3(not_x_y), .sel0(sel0), .sel1(sel1), .f(f));
endmodule

//-- Logic Unit 8 bit test
module test_logicUnit_8bit();
    reg [7:0] x, y;
    reg sel0, sel1;
    wire [7:0] f;
    logicUnit_8bit test(.x(x), .y(y), .sel0(sel0), .sel1(sel1), .f(f));
    initial begin
        $monitor("x=%b, y=%b, sel0=%b, sel1=%b | f=%b", x, y, sel0, sel1, f);
        x = 8'b10110010;
        y = 8'b00110101;
        sel0 = 1'b0;
        sel1 = 1'b0;
        #10
        sel0 = 1'b1;
        #10
        sel0 = 1'b0;
        sel1 = 1'b1;
        #10
        sel0 = 1'b1;
    end