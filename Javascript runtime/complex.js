var py_Complex = {
    return_a_complex_instance: function(_real, _imag) {
        var py_complex_instance = {};
        py_complex_instance.real = _real;
        py_complex_instance.imag = _imag ? _imag : 0;
        return py_complex_instance;
    },
    add : function(complex1, complex2) {
        return this.return_a_complex_instance(complex1.real + complex2.real,
                                   complex1.imag + complex2.imag);
    },
    sub : function(complex1, complex2) {
        return this.return_a_complex_instance(complex1.real - complex2.real,
                                   complex1.imag -complex2.imag);
    },
    mul : function(complex1,complex2) {
        var a = complex1.real;
        var b = complex1.imag;
        var c = complex2.real;
        var d = complex2.imag;
        return this.return_a_complex_instance(a * c - b * d,
                                   b * c + a * d);
    },
    div: function(complex1,complex2) {
        var a = complex1.real;
        var b = complex1.imag;
        var c = complex2.real;
        var d = complex2.imag;
        if (c == d && d == 0) return NaN;
        else return this.return_a_complex_instance(
        (a * c + b * d) / (c * c + d * d), (b * c - a * d) / (c * c + d * d));
    },
    floordiv: function(complex1, complex2) {
        var a = complex1.real;
        var b = complex1.imag;
        var c = complex2.real;
        var d = complex2.imag;
        if (c == d && d == 0) return NaN;
        else return this.return_a_complex_instance(
        Math.floor((a * c + b * d) / (c * c + d * d)), Math.floor((b * c - a * d) / (c * c + d * d)));
    },
    mod : function(complex1,complex2) {
        var a = complex1.real;
        var b = complex1.imag;
        var c = complex2.real;
        var d = complex2.imag;
        if (c == d && d == 0) return NaN;
        else return this.minus(complex1, this.product(this.floordiv(complex1, complex2), complex2));
    },
    neg : function(complex1) {
        return this.return_a_complex_instance(-complex1.real,-complex1.imag);
    },
    abs : function(complex1) {
        return this.return_a_complex_instance(
                                              complex1.real > 0?complex1.real:-complex1.real,
                                              complex1.imag > 0?complex1.imag:-complex1.imag);
    },
    conjugate : function(complex1) {
        return this.return_a_complex_instance(complex1.real,-complex1.imag);
    },
    divmod : function(complex1, complex2) {
        // todo
    },
    pow : function(complex1, num) {
        // todo
    }
}