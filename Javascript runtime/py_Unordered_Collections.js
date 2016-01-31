'use strict'

// Unordered Collections built-in Python.
// Include set, frozenset, dict

var print = console.log;		// define for debug

///////////////////////////////////////////////////////////////
//
//	prototype lists :
//		py_Set -> py_Set_Base -> Unordered_Collection ;
//		py_FrozenSet -> py_Set_Base -> Unordered_Collection ;
//		Dict -> Unordered_Collection ;
//
///////////////////////////////////////////////////////////////





// ----------------------------------------------
//     Unordered_Collection
// ----------------------------------------------

var py_Unordered_Collection = {

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

    // uc stands for unordered collection.

    return_an_instance : function() {
        var py_uc_instance = {};
        py_uc_instance.value = {};
        py_uc_instance.iter = null;     // iterator : index of keys

        py_uc_instance.next = function() {
            // get the next value
            var _key_list = Object.getOwnPropertyNames(this.value);

            if (this.iter === null) {
                this.iter = 0;
            } else if (++(this.iter) === _key_list.length) {
                this.iter = null;
                return undefined;
            }

            return this.value[_key_list[this.iter]];
        }

        return py_uc_instance;
    },
};





// ----------------------------------------------
//     Set Base
// ----------------------------------------------


// the Base Class of py_Set and py_FrozenSet
var py_Set_Base = {

    return_an_instance : function(_arr_of_obj) {
        var py_set_base_instance = py_Unordered_Collection.return_an_instance();

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
                } else if (_type_of_value === 'number') {
                    _ret_str = _ret_str.concat(i + ', ');
                } else {
                    _ret_str = _ret_str.concat(i + ', \n');
                }
            }
            if (_type_of_value === 'string' || _type_of_value === 'number') {
                var _shift = 2;
            } else {
                var _shift = 3;
            }
            
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
py_Set_Base.__proto__ = py_Unordered_Collection;





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

    opt_discard : function(_set, _obj) {
        if (this.opt_not_in(_set, _obj)) return _set;
        var _key = this.toKey(_obj);
        delete _set.value[_key];
        return _set;
    },

    opt_remove : function(_set, _obj) {
        if (this.opt_not_in(_set, _obj)) {
            throw "KeyError";
        }
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
        Object.freeze(py_frozenset_instance.value);     // freeze and lead to be immutable
        py_frozenset_instance.mutable = false;
        Object.freeze(py_frozenset_instance);
        return py_frozenset_instance;
    },
};
py_FrozenSet.__proto__ = py_Set_Base;





// ----------------------------------------------
//     Dict
// ----------------------------------------------

var KEY = 0, VALUE = 1;     // consist value for pair of key and value —— [key, value]

var py_Dict = {
    // store the pair of key and value into the Set

    // _arr_of_pair : [ [key1_obj, value1_obj], [key2_obj, value2_obj]... ]
    return_an_instance : function(_arr_of_pair) {
        var py_dict_instance = py_Unordered_Collection.return_an_instance();

        var _key;
        for (var i in _arr_of_pair) {
            _key = this.toKey(_arr_of_pair[i][KEY]);
            py_dict_instance.value[_key] = _arr_of_pair[i];
        }

        py_dict_instance.show = function() {
            var _arr = this.value;
            var _ret = "";
            for (var i in _arr) {
                _ret = _ret + '(' + _arr[i][KEY] + ' => ' + _arr[i][VALUE] + '), ';
            }
            _ret = '[ ' + _ret.substr(0, _ret.length - 2) + ']';
            return _ret;
        };

        return py_dict_instance;
    },

    opt_item : function(_dict, _key) {
        var _key_str = this.toKey(_key);
        return _dict.value[_key_str][VALUE];
    },

    opt_len : function(_dict) {
        return Object.getOwnPropertyNames(_dict.value).length;
    },

    opt_in : function(_dict, _key) {
        var _key_str = this.toKey(_key);
        return _key_str in _dict.value;
    },

    opt_not_in : function(_dict, _key) {
        return !this.opt_in(_dict, _key);
    },

    opt_set : function(_dict, _pair) {
        var _key = this.toKey(_pair[KEY]);
        _dict.value[_key] = _pair;
        return _dict;
    },

    opt_get : function(_dict, _obj) {
        // TODO();
    },

    opt_iter : function(_dict, _obj) {
        // TODO();
    },

    opt_next : function(_dict, _obj) {

    },

    opt_clear : function(_dict, _obj) {
        // TODO();
    },

    opt_items : function(_dict, _obj) {
        // TODO();
    },

    opt_pop : function(_dict, _obj) {
        // TODO();
    },

    opt_popitem : function(_dict, _obj) {
        // TODO();
    },

    opt_setdefault : function(_dict, _obj) {
        // TODO();
    },

    opt_update : function(_dict, _obj) {
        // TODO();
    },

    opt_values : function(_dict, _obj) {
        // TODO();
    },

};
py_Dict.__proto__ = py_Unordered_Collection;



///////////////////////////////////////////////////
// --------------------------------------------- //
//                    Testing.                   //
// --------------------------------------------- //
/////////////////////////////////////////////////// 


// --------------------- Test For Set ------------------------
print("****************** Test For Set ******************");
// test for numbers
print("----- test for numbers -----");
var set1 = py_Set.return_an_instance([2, 3, 1, 2]); 

print("len(set1) : " + py_Set.opt_len(set1));
print(set1.show());             // show
py_Set.opt_add(set1, 9);        // add
print(set1.show());

// iterator test
print("\niterator output : ");
var _item1 = set1.next();
while (_item1) {
    print(_item1);
    _item1 = set1.next();
}

print(set1.show());
print("pop() : " + py_Set.opt_pop(set1));    // pop
print(set1.show());
print(py_Set.opt_len(set1));    // len
print(py_Set.opt_remove(set1, 3).show());   // remove, nested



// test for strings
print("----- test for strings -----");
var set2 = py_Set.return_an_instance();
print("len(set2) : " + py_Set.opt_len(set2));

var set2_temp = ['ha', 'hey', 'hello', 'ha']
for (var _item2 in set2_temp) {
    py_Set.opt_add(set2, set2_temp[_item2]);
}

print("len(set2) : " + py_Set.opt_len(set2));
print(set2.show());             // show
py_Set.opt_add(set2, 'world');        // add
print(set2.show());
print(py_Set.opt_pop(set2));    // pop
print(set2.show());
print(py_Set.opt_len(set2));    // len
print(py_Set.opt_remove(set2, 'hey').show());   // remove, nested



// test for user-defined objects
print("----- test for user-defined objects -----");
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

// iterator test
print("\niterator output : ");
var _item3 = set3.next();
while (_item3) {
    print(_item3);
    _item3 = set3.next();
}

print('len(set3) : ' + py_Set.opt_len(set3));





// --------------------- Test For FrozenSet ------------------------

print("\n\n****************** Test For FrozenSet ******************");

var frozenset1 = py_FrozenSet.return_an_instance([2, 3, 1, 5, 7, 2]);
print(frozenset1.show());
print("If you attempt to change the value of a frozenset, then : ");
try {frozenset1.value = {1 : 1, 2 : 2, 3 : 3};} catch(e) {
    print("\t" + e);
}
print(frozenset1.show());


// --------------------- Test For Dict ------------------------

print("\n\n****************** Test For Dict ******************");

var dict1_temp = [['Zhao', 'Death'], ['Xi', 'Alive'], ['Da', 'Unknown']];
var dict1 = py_Dict.return_an_instance(dict1_temp);

print(dict1.show());
py_Dict.opt_set(dict1, ['Wang', 'Alive']);
print(dict1.show());
py_Dict.opt_set(dict1, ['Wang', 'Death']);
print(dict1.show());

// iterator test
print("\niterator output : ");
var _item4 = dict1.next();
while (_item4) {
    print(_item4);
    _item4 = dict1.next();
}