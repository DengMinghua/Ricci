function Available(_ele) {
    return (typeof _ele != "undefined" && _ele !== null);
}

function is_in_array(_array, _ele) {
    if (_array === null || typeof _array != "undefined") return false;
    for (var i = 0, l = _array.length; i < l; i++) {
        if (array[i] == _ele) {
            return true;
        }
    }
    return false;
}

function forEach(array, func) {
    for (var i = 0, l = array.length; i < l; i++) {
        func(array[i]);
    }
}

function extend_from_class(_derived_class, _base_class) {
    var temp = null;
    var derived_class_con = _derived_class.constructor;
    var proto = derived_class_con.prototype;
    var some = {};

    for (temp in proto) {
        some[temp] = "Ban";
    }

    if (typeof _base_class.derived_class == "undefined") {
        _base_class.derived_class = {
            class_constructor: _base_class,
            derived_class_list: []
        };
    }

    _derived_class.derived_class = {
        classConstructor: derived_class_con,
        derived_class_list: []
    };

    _base_class.derived_class.derived_class_list.push(_derived_class.derived_class);

    for (temp in _base_class.prototype) {
        if (!some[temp] && !is_in_array(_base_class._jpp_privateList, k)) {
            proto[temp] = baseClass.prototype[temp];
        }
    }

    derived_class_con.private_list = _base_class.private_list;
    derived_class_con.protected_list = _base_class.protected_list
    derived_class_con.public_list = _base_class.public_list;


    _base_class.extend = true;
    _base_class.current_derived_class = _derived_class;
    _base_class.apply(_derived_class, []);
    _base_class.current_derived_class = null;
    _base_class.extend = false;
}

function return_a_class_instance(list) {
    function py_Class() {
        var temp = null,
            ext = list["extends"],
            pri = list["private"],
            pro = list["protect"],
            pub = list["public"],
            sta = list["static"],
            properties_and_methods = []
        var temp = null;
        if (ext) {
            extend_from_class(py_Class, ext);
        }

        if (!Available(py_Class.private_list)) {
            py_Class.private_list = [];
        }

        if (!Available(py_Class.protected_list)) {
            py_Class.protected_list = [];
        }

        if (!Available(py_Class.public_list)) {
            py_Class.public_list = [];
        }

        if (pri) {
            for (temp in pri) {
                py_Class.private_list.push(temp);
                properties_and_methods.push({
                    name: temp,
                    content: pri[temp],
                    isPrivate: true
                });
            }
        }

        if (pro) {
            for (temp in pro) {
                py_Class.protected_list.push(temp);
                properties_and_methods.push({
                    name: temp,
                    content: pro[temp],
                    isProtected: true
                });
            }
        }

        if (pub) {
            for (temp in pub) {
                var val = temp;
                if (val == "constructor")
                    val = "con";
                py_Class.public_list.push(val);
                properties_and_methods.push({
                    name: val,
                    content: pub[temp]
                });
            }
        }

        if (sta) {
            for (temp in sta) {
                py_Class[temp] = sta[temp];
            }
        }

        if (!Available(py_Class.properties_and_methods_list)) {
            py_Class.properties_and_methods_list = {};
        }

        forEach(properties_and_methods, function(_ele) {
            var name = _ele.name;
            var content = _ele.content;

            if (_ele.isPrivate && py_Class.is_extend) {
                return;
            }

            if (typeof content != "function")
                py_Class[name] = content;
            else {
                var f = function() {
                    py_Class.called = true;
                    var res = content.apply(py_Class, arguments);
                    py_Class.called = false;
                    return res;
                };
                py_Class.constructor.prototype[name] = f;
            }
            py_Class.properties_and_methods_list[name] = content;

            if (_ele.isPrivate || _ele.isProtected) {
                var flag = _ele.isProtected ? "protected" : "private";

                Object.defineProperty(py_Class, _ele.name, {
                    get: function() {
                        if (!Available(py_Class.called)) {
                            throw new RangeError(name + " is " + flag);
                        }
                        return py_Class.properties_and_methods_list[name];
                    },

                    set: function(_value) {
                        if (!Available(py_Class.called)) {
                            throw new RangeError(name + " is " + flag);
                        }
                        py_Class.properties_and_methods_list[name] = _value;
                    }
                });
            }
        });
        if (typeof py_Class.con == "function") {
            if (!py_Class.extend) {
                py_Class.con.apply(py_Class, arguments);
            } else {
                py_Class.current_derived_class.super = py_Class.con;
            }
        }
        return py_Class;
    }
    return py_Class;
}

var Class = return_a_class_instance;

var People = Class({
    extends: null,
    private: {
        id: null
    },
    public: {
        constructor: function(_id) {
            this.id = _id;
        },

        get_id: function() {
            return this.id;
        }
    }
});

var Student = Class({
    extends: People,
    private: {
        name: null
    },
    public: {
        constructor: function(_id, _name){
            this.super(_id);
            this.name = _name;
        },

        get_name: function() {
            return this.name;
        }
    }
})

var b = new Student(14331052,"ming");
var d = new Student(14331053,"ting");
var c = b.get_name();
alert(c);
