module mux2to1 (
    sel, i1, i0, f
);
    input i0, i1, sel;
    output f;
    and(a, i0, nsel);
    and(b, i1, sel);
    not(nsel, sel);
    or (f, a, b);
endmodule