//-- Mux 4 to 1
module mux4x1(
    i3, i2, i1, i0, sel1, sel0, f
);
    input i3, i2, i1, i0, sel1, sel0;
    output f;
    not(nsel1, sel1);
    not(nsel0, sel0);
    and(and_i0_nsel1_nsel0,
        i0,
        nsel1,
        nsel0
    );
    and(and_i1_sel1_nsel0,
        i1,
        sel1,
        nsel0
    );
    and(and_i2_nsel1_sel0,
        i2,
        nsel1,
        sel0
    );
    and(and_i3_sel1_sel0,
        i3,
        sel1,
        sel0
    );
    or(f,
        and_i0_nsel1_nsel0,
        and_i1_sel1_nsel0,
        and_i2_nsel1_sel0,
        and_i3_sel1_sel0
    );
endmodule

module test_mux4x1();
    reg i3, i2, i1, i0, sel1, sel0;
    wire f;
    mux4x1 mux(
        .i0(i0),
        .i1(i1),
        .i2(i2),
        .i3(i3),
        .sel0(sel0),
        .sel1(sel1),
        .f(f)
    );
    initial begin
        $monitor("\033[0;36mi0 = %b, i1 = %b, i2 = %b, i3 = %b \033[0m|\033[0;33m s1 = %b, s0 = %b\033[0m | f = %b", i0, i1, i2, i3, sel1, sel0, f);
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