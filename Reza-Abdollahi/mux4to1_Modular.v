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

module test_mux4x1();
    reg i0, i1, i2, i3, sel0, sel1;
    wire f;
    mux4x1 test(.i0(i0), .i1(i1), .i2(i2), .i3(i3), .sel0(sel0), .sel1(sel1), .f(f));
    initial begin
        $monitor("i0=%b, i1=%b, i2=%b, i3=%b, sel0=%b, sel1=%b | f=%b", i0, i1, i2, i3, sel0, sel1, f);
        sel0 = 1'b0;
        sel1 = 1'b0;
        i0 = 1'b0;
        #10
        i0 = 1'b1;
        #10
        sel0 = 1'b1;
        i1 = 1b'0;
        #10
        i1 = 1'b1;
        #10
        sel1 = 1'b1;
        sel0 = 1'b0;
        i2 = 1'b0;
        #10
        i2 = 1'b1
        #10
        sel0 = 1'b1;
        i3 = 1'b0;
        #10
        i3 = 1'b1;
    end
endmodule