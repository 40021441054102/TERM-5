module mux4x1(
    i0, i1, i2, i3, sel0, sel1, f
);
    input i0, i1, i2, i3, sel0, sel1;
    output f;
    not(nsel0, sel0);
    not(nsel1, sel1);
    and(and_i0_nsel0_nsel1, i0, nsel0, nsel1);
    and(and_i1_nsel0_sel1, i1, nsel0, sel1);
    and(and_i2_sel0_nsel1, i2, sel0, nsel1);
    and(and_i3_sel0_sel1, i3, sel0, sel1);
    or(
        f,
        and_i0_nsel0_nsel1,
        and_i1_nsel0_sel1,
        and_i2_sel0_nsel1,
        and_i3_sel0_sel1
    );
endmodule

module test_mux4x1();
    reg i0, i1, i2, i3, sel0, sel1;
    wire f;
    mux4x1 test(.i0(i0), .i1(i1), .i2(i2), .i3(i3), .sel0(sel0), .sel1(sel1), .f(f));
    initial begin
        i0 = 1'b1;
        i1 = 1'b0;
        i2 = 1'b0;
        i3 = 1'b0;
        sel0 = 1'b0;
        sel1 = 1'b0;
        #10
        i0 = 1'b0;
        i1 = 1'b1;
        i2 = 1'b0;
        i3 = 1'b0;
        sel0 = 1'b0;
        sel1 = 1'b1;
        #10
        i0 = 1'b0;
        i1 = 1'b0;
        i2 = 1'b1;
        i3 = 1'b0;
        sel0 = 1'b1;
        sel1 = 1'b0;
        #10
        i0 = 1'b0;
        i1 = 1'b0;
        i2 = 1'b0;
        i3 = 1'b1;
        sel0 = 1'b1;
        sel1 = 1'b1;
        #10
        i0 = 1'b0;
        i1 = 1'b1;
        i2 = 1'b1;
        i3 = 1'b1;
        sel0 = 1'b0;
        sel1 = 1'b0;
        #10
        i0 = 1'b1;
        i1 = 1'b0;
        i2 = 1'b1;
        i3 = 1'b1;
        sel0 = 1'b0;
        sel1 = 1'b1;
        #10
        i0 = 1'b1;
        i1 = 1'b1;
        i2 = 1'b0;
        i3 = 1'b1;
        sel0 = 1'b1;
        sel1 = 1'b0;
        #10
        i0 = 1'b1;
        i1 = 1'b1;
        i2 = 1'b1;
        i3 = 1'b0;
        sel0 = 1'b1;
        sel1 = 1'b1;
    end
endmodule