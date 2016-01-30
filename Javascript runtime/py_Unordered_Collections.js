'use strict'

// Unordered Collections built-in Python.
// Include set, frozenset, dict

var print = console.log;		// define for debug

///////////////////////////////////////////////////////
//
//	prototype lists :
//		py_Set -> py_Set_Base ;
//		py_FrozenSet -> py_Set_Base ;
//		Dict ;
//
///////////////////////////////////////////////////////



// ----------------------------------------------
//     Set Base
// ----------------------------------------------


// the Base Class of py_Set and py_FrozenSet
var py_Set_Base = {

// ---------------------------------------------------------------------
// -*- Auxiliary Function -*-

    // hash function 
    Hash_Obj_to_Str : function(_obj) {
        /*  check if the _obj is hashable. (if isFrozen or not)
        if (typeof _obj === 'object' && !Object.isFrozen(_obj)) {
            Object.freeze(_obj);
        }
        */
        var _hash_str = JSON.stringify(_obj);
        return _hash_str;
    },

    // transform the _obj to a hashable key(string).
    toKey : function(_obj) {

        // String and Number could be the key.
        if (typeof(_obj) === 'string' || typeof(_obj) === 'number') {
            return _obj;
        }

        // Object and other types
        return this.Hash_Obj_to_Str(_obj);
    },

// ---------------------------------------------------------------------

    return_an_instance : function(_arr_of_obj) {
        var py_set_base_instance = {};
        py_set_base_instance.value = {};

        var _key;
        for (var i in _arr_of_obj) {
            _key = this.toKey(_arr_of_obj[i]);
            py_set_base_instance.value[_key] = _arr_of_obj[i];
        }
        
        // return a string of all keys.
        py_set_base_instance.show = function() {
            var _ret_str = "";
            var _type_of_value;
            for (var i in this.value) {
                _type_of_value = typeof this.value[i];
                if (_type_of_value === 'string') {
                    _ret_str = _ret_str.concat('\'' + i + '\', ');
                } else {
                    _ret_str = _ret_str.concat(i + ', \n');
                }
            }
            var _shift = _type_of_value === 'string' ? 2 : 3;
            _ret_str = 'py_Set : {' + _ret_str.substr(0, _ret_str.length - _shift) + '}';
            return _ret_str;
        };

        return py_set_base_instance;
    },

    opt_in : function(_set_base, _obj) {
        var _key = this.toKey(_obj);
        return _key in _set_base.value;
    },

    opt_not_in : function(_set_base, _obj) {
        return !this.opt_in(_set_base, _obj);
    },

    opt_len : function(_set) {
        return Object.getOwnPropertyNames(_set.value).length;
    },

    opt_empty : function(_set) {
        return this.opt_len(_set) === 0;
    },

    opt_isdisjoint : function(_set_base, _subset) {
        // TODO()
    },

    opt_issubset : function(_set_base, _subset) {
        // TODO()
    },

    opt_issuperset : function(_set_base, _supset) {
        // TOOD();
    },

    opt_union : function(_set_base, _another_set_base) {
        // TODO();
    },

    opt_intersection : function(_set_base, _another_set_base) {
        // TODO();
    },

    opt_difference : function(_set_base, _another_set_base) {
        // TODO();
    },

    opt_symmetric_difference : function(_set_base, _another_set_base) {
        // TODO();
    },

    opt_copy : function(_set_base, _another_set_base) {
        // TODO();
    },
};


// ----------------------------------------------
// 	   Set
// ----------------------------------------------

var py_Set = {

    return_an_instance : function(_arr_of_obj) {
        var py_set_instance = py_Set_Base.return_an_instance(_arr_of_obj);
        py_set_instance.mutable = true;
        return py_set_instance;
    },

    opt_in : function(_set, _obj) {
        var _key = this.toKey(_obj);
        return _key in _set.value;
    },

    opt_not_in : function(_set, _obj) {
        return !this.opt_in(_set, _obj);
    },

    opt_add : function(_set, _obj) {
        if (this.opt_in(_set, _obj)) return _set;
        var _key = this.toKey(_obj);
        _set.value[_key] = _obj;
        return _set;
    },

    opt_remove : function(_set, _obj) {
        if (this.opt_not_in(_set, _obj)) return _set;
        var _key = this.toKey(_obj);
        delete _set.value[_key];
        return _set;
    },

    opt_pop : function(_set) {
        var _value;
        for (var i in _set.value) {
            _value = _set.value[i];
            delete _set.value[i];
            break;
        }
        
        return _value;
    },

    opt_discard : function(_set) {
        // TODO();
    },

    opt_update : function(_set) {
        // TODO();
    },
    opt_intersection_update : function(_set) {
        // TODO();
    },
    opt_difference_update : function(_set) {
        // TODO();
    },
    opt_symmetric_difference_update : function(_set) {
        // TODO();
    },
};
py_Set.__proto__ = py_Set_Base;


// ----------------------------------------------
//     FrozenSet
// ----------------------------------------------

var py_FrozenSet = {
    return_an_instance : function(_arr_of_obj) {
        var py_frozenset_instance = py_Set_Base.return_an_instance(_arr_of_obj);
        py_frozenset_instance.mutable = false;
        return py_frozenset_instance;
    },
};
py_FrozenSet.__proto__ = py_Set_Base;


// ----------------------------------------------
//     Dict
// ----------------------------------------------

var Dict = {
    return_an_instance : function(_arr_of_obj) {
        // TODO();
    },
};




///////////////////////////////////////////////////
// --------------------------------------------- //
//                    Testing.                   //
// --------------------------------------------- //
/////////////////////////////////////////////////// 


// test for numbers
var set1 = py_Set.return_an_instance([2, 3, 1, 2]); 

print("len(set1) : " + py_Set.opt_len(set1));
print(set1.show());             // show
py_Set.opt_add(set1, 9);        // add
print(set1.show());
print(py_Set.opt_pop(set1));    // pop
print(set1.show());
print(py_Set.opt_len(set1));    // len
print(py_Set.opt_remove(set1, 3).show());   // remove, nested

// test for strings
var set2 = py_Set.return_an_instance(['ha', 'hey', 'hello', 'ha']); 

print("len(set2) : " + py_Set.opt_len(set2));
print(set2.show());             // show
py_Set.opt_add(set2, 'world');        // add
print(set2.show());
print(py_Set.opt_pop(set2));    // pop
print(set2.show());
print(py_Set.opt_len(set2));    // len
print(py_Set.opt_remove(set2, 'hey').show());   // remove, nested

// test for user-defined objects
var Student = function(_name) {
    this.name = _name;
    this.id = ++id_count;
};

var id_count = 0;

// create the instances of Student
var stu_arr = []
for (var i = 0; i < 5; i++) {
    var _number = Math.floor((Math.random() * 10));
    var _tmp = new Student("XiaoMing " + _number.toString());
    stu_arr.push(_tmp);
}

print(stu_arr);

var set3 = py_Set.return_an_instance(stu_arr);
print(set3.show());
var stu1 = new Student("XiaoHong");
py_Set.opt_add(set3, stu1);
print(set3.show());
print('len(set3) : ' + py_Set.opt_len(set3));