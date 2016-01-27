'use strict'

// Python built-in Type Class

var print = console.log;		// define for debug

// Container for Sequence Types -- list, tuple, range
//       and for Unordered Types -- set, dict ;

// *************************************************
// warning :  sets do not support indexing, slicing, 
// 			  or other sequence-like behavior.


// ----------------------------------------------
// Do now.
// ----------------------------------------------


// class Container
var Container = {
	create_Container : function() {
		var py_container = {};
		// Void...
		return py_container;
	},
};


// class Sequence
var Sequence = {
	create_Sequence : function(_value) {

		if (Array.isArray(_value)) {
			var py_sequence = _value;
		} else {
			var py_sequence = new Array(_value);
		}
		
		return py_sequence;
	},

	opt_in : function(_element, _arr) {
		// Make sure arguments' types
		if (Array.isArray(_element)) {
			_element = [_arr, _arr = _element][0];	// Swap inline
		}

		var _ret = _arr.indexOf(_element) !== -1;
		return _ret;
	},

	opt_not_in : function(_element, _value) {
		return !Sequence.opt_in(_element, _value);
	},

	opt_add : function(_value1, _value2) {
		return _value1.concat(_value2);
	},

	// Shallow copying is supported!
	opt_mul : function(_value1, _value2) {
		// Make sure that _value1 is a number and _value2 is an array.
		if (Array.isArray(_value1)) {
			_value1 = [_value2, _value2 = _value1][0];	// Swap inline
		}
		
		var _ret = [];
		for (var i = 0; i < _value1; i++) {
			_ret = _ret.concat(_value2);
		}
		return _ret;
	},

	opt_item : function(_arr, _index) {
		return _arr[_index];
	},

	opt_slice : function(_arr, _left, _right) {
		return _arr.slice(_left, _right);
	},

	opt_index : function(_arr, _element, _left, _right) {
		var _tmpArr = Sequence.opt_slice(_arr, _left, _right);
		var _index = _tmpArr.indexOf(_element) + _left;
		return _index;
	},

	opt_slice_step : function(_value, _value1, _value2, _step) {
		// _step cannot be zero
		var _ret = [];

		if ((_value2 - _value1) * _step < 0) return _ret;
		
		if (_step > 0) {
			for (var i = _value1; i < _value2; i += _step) {
				_ret.push(_value[i]);
			}
		} else if (_step < 0) {
			for (var i = _value1; i > _value2; i += _step) {
				_ret.push(_value[i]);
			}
		}
		return _ret;
	},

	opt_len : function(_value) {
		return _value.length;
	},

	opt_min : function(_arr) {
		var _min = _arr[0];
		for (var i = 1; i < _arr.length; i++) {
			if (_min > _arr[i]) _min = _arr[i];
		}
		return _min;
	},

	opt_max : function(_arr) {
		var _max = _arr[0];
		for (var i = 1; i < _arr.length; i++) {
			if (_max < _arr[i]) _max = _arr[i];
		}
		return _max;
	},

	opt_count : function(_arr, _value) {
		var _ret = 0;
		for (var i in _arr) {
			if (_arr[i] === _value) ++_ret;
		}
		return _ret;
	},

	// *********************************************************************
	//	Python Official Documents :
	//
	//		Tuples and lists are compared lexicographically using comparison 
	//	of corresponding elements. This means that to compare equal, each
	//	element must compare equal and the two sequences must be of the
	//	same type and have the same length.
	//
	//		If not equal, the sequences are ordered the same as their first
	//	differing elements. For example, [1,2,x] <= [1,2,y] has the same
	//	value as x <= y. If the corresponding element does not exist, the
	//	shorter sequence is ordered first (for example, [1,2] < [1,2,3]).
	//
	// *********************************************************************
	// opt_compare(_value1, _value2) : return 1 if _value1 > _value2,
	//							 	   return -1 if _value1 < _value2,
	//								   return 0 if _value1 === _value2.

	opt_compare : function(_value1, _value2) {
		var _len1 = _value1.length, _len2 = _value2.length;

		var _len = Math.min(_len1, _len2);
		for (var i = 0; i < _len; i++) {
			if (_value1[i] !== _value2[i]) {
				return _value1[i] > _value2[i] ? 1 : -1;
			}
		}

		if (_len1 === _len2) return 0;
		return _len1 > _len2 ? 1 : -1;
	},
};


// class Unordered_Container
var Unordered_Container = {
	create_Unordered_Container : function() {
		var py_unordered_container = Container.create_Container();
		// TODO();
		return py_unordered_container;
	},
};

// class Mutable_Sequence
var Mutable_Sequence = {
	create_Mutable_Sequence : function(_value) {
		var py_mutable_sequence = Sequence.create_Sequence(_value);
		return py_mutable_sequence;
	},

	opt_slice_get : Sequence.opt_slice,

	opt_slice_set : function(_arr, _left, _right, _value) {
		var _ret = _arr.slice(0, _left);
		if (typeof(_value) !== 'undefined') {
			_ret = _ret.concat(_value);
		}
		_ret = _ret.concat(_arr.slice(_right));
		for (var i in _ret) {
			_arr[i] = _ret[i];
		}
		_arr.length = _ret.length;
		return _arr;
	},

	opt_item_set : function(_mseq, _index, _value) {
		_mseq[_index] = _value;
	},

	opt_item_get : Sequence.opt_item,

	opt_del : function(_arr, _left, _right) {
		Mutable_Sequence.opt_slice_set(_arr, _left, _right)
	},

	opt_append : function(_arr, _value) {
		_arr.push(_value);
	},

	opt_clear : function(_arr) {
		_arr.length = 0;
	},

	opt_copy : function(_arr) {
		var tmp = _arr.splice();
		return tmp;
	},

	opt_extend : function(_arr1, _arr2) {
		_arr1 = _arr1.concat(_arr2);
	},

	opt_pop : function(_arr, _index) {
		_arr.splice(_index, 1);
	},

	opt_remove : function(_arr, _value) {
		Mutable_Sequence.opt_pop(_arr, _arr.indexOf(_value));
	},

	opt_reverse : function(_arr) {
		return _arr.reverse();
	},
};
Mutable_Sequence.__proto__ = Sequence;	// inheritance


// class List
var List = {
	create_List : function(_value) {
		var py_list_instance = Mutable_Sequence.create_Mutable_Sequence(_value);
		return py_list_instance;
	},

	opt_sort : function(_lis, _comp_func) {
		return _lis.sort(_comp_func);
	},

};
List.__proto__ = Mutable_Sequence;	// inheritance



// class Immutable_Sequence
var Immutable_Sequence = {
	create_Immutable_Sequence : function(_value) {
		var py_immutable_sequence = Sequence.create_Sequence(_value);
		return py_immutable_sequence;
	},
};
Immutable_Sequence.__proto__ = Sequence;	// inheritance


// class Tuple
var Tuple = {
	create_Tuple : function(_value) {
		var py_tuple_instance = Immutable_Sequence.create_Immutable_Sequence(_value);
		return py_tuple_instance;
	},
};
Tuple.__proto__ = Immutable_Sequence;	// inheritance


// class Range
var Range = {
	create_Range : function(_value1, _value2, _value3) {
		var _ret = [];

		if (_value3 && _value3 * (_value2 - _value1) <= 0) {
			return _ret;
		}

		var _start = 0;
		var _stop = _value1;
		var _step = _value3 || 1;

		if (typeof(_value2) !== 'undefined') {
			var _start = _value1;
			var _stop = _value2;
		}

		if (_step > 0) {
			for (var i = _start; i < _stop; i += _step) {
				_ret.push(i);
			}
		} else {
			for (var i = _start; i > _stop; i += _step) {
				_ret.push(i);
			}
		}

		var py_range_instance = Sequence.create_Sequence(_ret);
		print(py_range_instance);
		return py_range_instance;
	},
};

// class Set
var Set = {
	create_Set : function() {
		// TODO();
	},
};

// class Frozenset
var Frozenset = {
	create_Frozenset : function() {
		// TODO();
	},
};

// class Dict
var Dict = {
	create_Dict : function() {
		// TODO();
	},
};

// ----------------------------------------------
// Additional Types -- string, bytes, bytearray
// ----------------------------------------------

// class String
var String = {
	create_String : function() {
		// TODO();
	},

	// Operater "in" Overloads in String.
	// i.e.
	// >>> "gg" in "eggs"
	// True
	opt_in : function() {
		// TODO();
	},
};

// class Bytes
var Bytes = {
	create_Bytes : function() {
		// TODO();
	},
};

// class Bytearry
var Bytearry = {
	create_Bytearry : function() {
		// TODO();
	},
};

// ----------------------------------------------
// Testing.
// ----------------------------------------------


/*
var mseq_Ins1 = Mutable_Sequence.create_Mutable_Sequence([7, 6, 5, 4, 3]);

var test_list = [
	"-------------- create function -------------",
	Container.create_Container(),
	Sequence.create_Sequence(),
	Unordered_Container.create_Unordered_Container(),
	Mutable_Sequence.create_Mutable_Sequence(),
	Immutable_Sequence.create_Immutable_Sequence(),
	List.create_List(),
	Tuple.create_Tuple(),
	Range.create_Range(),
	Dict.create_Dict(),
	String.create_String(),

	"-------------- Sequence function -------------",
	Sequence.opt_in(2, [0, 1, 2, 5]),	// true
	Sequence.opt_in([0, 1, 2, 5], 0),	// true
	Sequence.opt_in(3, [0, 1, 2, 5]),	// false

	Sequence.opt_not_in(3, [0, 1, 2, 5]),	// true
	Sequence.opt_add([1, 2], [3, 4]),	// [1, 2, 3, 4]
	Sequence.opt_len([1, 2, 3]),		// 3

	Sequence.opt_mul(3, [1, 2, 3]),		// [1, 2, 3, 1, 2, 3, 1, 2, 3]
	Sequence.opt_mul([1, 2, 3], 3),		// [1, 2, 3, 1, 2, 3, 1, 2, 3]
	Sequence.opt_mul([[]], 3),			// [[], [], []]

	Sequence.opt_slice([1, 2, 3, 4, 5], 1, 3),	// [2, 3]

	Sequence.opt_slice_step([0, 1, 2, 3, 4, 5], 1, 4, 2),	// [1, 3]
	Sequence.opt_slice_step([0, 1, 2, 3, 4, 5], 1, 4, -1),	// []
	Sequence.opt_slice_step([0, 1, 2, 3, 4, 5], 4, 0, -1),	// [4, 3, 2]

	Sequence.opt_count([2, 3, 2, 2, 6, 5, 6], 2),	// 3
	Sequence.opt_index([1, 2, 3, 4, 5], 3, 1, 3),	// 2
	Sequence.opt_index([1, 2, 3, 4, 5], 3, 1),		// 2

	Sequence.opt_min([2, 3, 2, 1, 9, 6, 5, 6]),		// 1
	Sequence.opt_max([2, 3, 2, 1, 9, 6, 5, 6]),		// 9

	Sequence.opt_compare([1, 2, 'x'], [1, 2, 'x']),	// 0
	Sequence.opt_compare([1, 2, 'y'], [1, 2, 'x']),	// 1
	Sequence.opt_compare([1, 2, 'x'], [1, 2, 'y']),	// -1

	"-------------- Mutable_Sequence function -------------",
	Mutable_Sequence.opt_slice([1, 2, 3, 4, 5], 1, 3),		// [2, 3]
	Mutable_Sequence.opt_slice_get([1, 2, 3, 4, 5], 1, 4),	// [2, 3, 4]
	
	Mutable_Sequence.opt_slice_set(mseq_Ins1, 2, 3, [99, 98]),
	// [7, 6, 99, 98, 4, 3]
	Mutable_Sequence.opt_slice_set(mseq_Ins1, 4, 5, 100),
	// [7, 6, 99, 98, 100, 4, 3]

	"-------------- Range Creation -------------",
	Range.create_Range(6),	// [0, 1, 2, 3, 4, 5]
	Range.create_Range(1, 10, 2),	// [1, 3, 5, 7, 9]
	Range.create_Range(7, 3, -1), 	// [7, 6, 5, 4]
	
];

for (var i in test_list) {
	print(test_list[i]);
}
*/