'use strict'

// Sequence built-in python.
// include list, tuple, range, string, bytes

var print = console.log;		// define for debug

// ----------------------------------------------
// 	   Sequence 
// ----------------------------------------------


var Sequence = {
	return_a_instance : function(_arr) {
		var sequence_instance = {};
		sequence_instance.value = _arr;
		sequence_instance.get_value = function() {
			return this.value;
		}
		return sequence_instance;
	},



	opt_in : function(_element, _seq) {
		// Make sure arguments' types
		if (typeof(_element) === 'object' && 'value' in _element) {
			_element = [_seq, _seq = _element][0];	// Swap inline
		}
		var _ret = _seq.get_value().indexOf(_element) !== -1;
		return _ret;
	},

	opt_not_in : function(_element, _seq) {
		return !this.opt_in(_element, _seq);
	},

	opt_add : function(_seq1, _seq2) {		
		return this.return_a_instance(_seq1.get_value().concat(_seq2.get_value()));
	},

	// Shallow copying is supported!
	opt_mul : function(_num, _seq) {
		// Make sure that argument 1 is a number and argument 2 is a sequence.
		if (isNaN(_num)) {
			_num = [_seq, _seq = _num][0];	// Swap inline
		}
		
		var _ret = [];
		for (var i = 0; i < _num; i++) {
			_ret = _ret.concat(_seq.get_value());
		}

		return this.return_a_instance(_ret);
	},

	opt_item : function(_seq, _index) {
		return _seq.get_value()[_index];
	},

	opt_slice : function(_seq, _left, _right) {
		return this.return_a_instance(_seq.get_value().slice(_left, _right));
	},

	opt_index : function(_seq, _element, _left, _right) {
		var _tmpSeq = this.opt_slice(_seq, _left, _right);
		var _index = _tmpSeq.get_value().indexOf(_element);
		return _index === -1 ? -1 : _index + _left;
	},

	opt_slice_step : function(_seq, _value1, _value2, _step) {
		// _step cannot be zero
		var _ret = [];

		if ((_value2 - _value1) * _step < 0) return _ret;
		
		if (_step > 0) {
			for (var i = _value1; i < _value2; i += _step) {
				_ret.push(_seq.get_value()[i]);
			}
		} else if (_step < 0) {
			for (var i = _value1; i > _value2; i += _step) {
				_ret.push(_seq.get_value()[i]);
			}
		}
		return this.return_a_instance(_ret);
	},

	opt_len : function(_seq) {
		return _seq.get_value().length;
	},

	opt_min : function(_seq) {
		var _min = _seq.get_value()[0];
		for (var i = 1; i < _seq.get_value().length; i++) {
			if (_min > _seq.get_value()[i]) _min = _seq.get_value()[i];
		}
		return _min;
	},

	opt_max : function(_seq) {
		var _max = _seq.get_value()[0];
		for (var i = 1; i < _seq.get_value().length; i++) {
			if (_max < _seq.get_value()[i]) _max = _seq.get_value()[i];
		}
		return _max;
	},

	opt_count : function(_seq, _value) {
		var _count = 0;
		for (var i in _seq.get_value()) {
			if (_seq.get_value()[i] === _value) ++_count;
		}
		return _count;
	},

	// ************************************************************************
	//	Python Official Documents :
	//
	//	    Tuples and lists are compared lexicographically using comparison 
	//	of corresponding elements. This means that to compare equal, each
	//	element must compare equal and the two sequences must be of the
	//	same type and have the same length.
	//
	//	    If not equal, the sequences are ordered the same as their first
	//	differing elements. For example, [1,2,x] <= [1,2,y] has the same
	//	get_value() as x <= y. If the corresponding element does not exist, the
	//	shorter squence is ordered first (for example, [1,2] < [1,2,3]).
	//
	// ************************************************************************
	// opt_compare(_seq1, _seq2) : 
	// 			return 1 if _seq1 > _seq2,
	//			return -1 if _seq1 < _seq2,
	//			return 0 if _seq1 === _seq2.

	opt_compare : function(_seq1, _seq2) {
		var _len1 = _seq1.get_value().length, _len2 = _seq2.get_value().length;

		var _len = Math.min(_len1, _len2);
		for (var i = 0; i < _len; i++) {
			if (_seq1.get_value()[i] !== _seq2.get_value()[i]) {
				return _seq1.get_value()[i] > _seq2.get_value()[i] ? 1 : -1;
			}
		}

		if (_len1 === _len2) return 0;
		return _len1 > _len2 ? 1 : -1;
	},
};









// ----------------------------------------------
//     Mutable_Sequence
// ----------------------------------------------


var Mutable_Sequence = {
	return_a_instance : function(_arr) {
		var mutable_sequence_instance = Sequence.return_a_instance(_arr);
		return mutable_sequence_instance;
	},

	opt_slice_get : function(_mseq, _left, _right) {
		return this.opt_slice(_mseq, _left, _right);
	},

	opt_slice_set : function(_mseq, _left, _right, _value) {
		var _ret = this.opt_slice_get(_mseq, 0, _left).value;		// get left part
		
		if (typeof(_value) !== 'undefined') {			// set the middle part
			_ret.concat(_value);
		}
		_ret = _ret.concat(this.opt_slice_get(_mseq, _right).value);	// get right part
		_mseq.value = _ret;		// set the value
		return _mseq;
	},

	opt_item_set : function(_mseq, _index, _value) {
		_mseq.value[_index] = _value;
		return _mseq;
	},

	opt_item_get : function(_mseq, _index) {
		return this.opt_item(_mseq, _index);
	},

	opt_del : function(_mseq, _left, _right) {
		_mseq.value.splice(_left, _right - _left);
		return _mseq;
	},

	opt_append : function(_mseq, _value) {
		_mseq.value.push(_value);
		return _mseq;
	},

	opt_clear : function(_mseq) {
		_mseq.length = 0;
		return _mseq;
	},

	opt_copy : function(_mseq) {
		var tmp = this.return_a_instance(_mseq.value);
		return tmp;
	},

	opt_extend : function(_mseq1, _mseq2) {
		return this.opt_add(_mseq1, _mseq2);
	},

	opt_pop : function(_mseq, _index) {
		_mseq.splice(_index, 1);
		return _mseq;
	},

	opt_remove : function(_mseq, _value) {
		this.opt_pop(_mseq, _mseq.value.indexOf(_value));
	},

	opt_reverse : function(_mseq) {
		_mseq.value.reverse();
		return _mseq;
	},
};
Mutable_Sequence.__proto__ = Sequence;	// Inheritance






// ----------------------------------------------
//     List
// ----------------------------------------------

var List = {
	return_a_instance : function(_arr) {
		var list_instance = Mutable_Sequence.return_a_instance(_arr);
		return list_instance;
	},

	opt_sort : function(_lis, _comp_func) {
		return _lis.value.sort(_comp_func);
	},
};
List.__proto__ = Mutable_Sequence;	// Inheritance





// ----------------------------------------------
//     Immutable_Sequence
// ----------------------------------------------

var Immutable_Sequence = {
	return_a_instance : function(_arr) {
		var immutable_sequence_instance = Sequence.return_a_instance(_arr);
		var private_value = _arr;
		immutable_sequence_instance.get_value = function() {
			var _private_value_copy = private_value.slice();
			return _private_value_copy;
		};
		return immutable_sequence_instance;
	},
};
Immutable_Sequence.__proto__ = Sequence;	// Inheritance


// ----------------------------------------------
//     Tuple
// ----------------------------------------------

var Tuple = {
	return_a_instance : function(_arr) {
		var tuple_instance = Immutable_Sequence.return_a_instance(_arr);
		return tuple_instance;
	},
};
Tuple.__proto__ = Immutable_Sequence;	// Inheritance


// ----------------------------------------------
//     Range
// ----------------------------------------------

var Range = {
	return_a_instance : function(_value1, _value2, _value3) {

		// **************************************
		//   Range(5)       -> ( 0, 1, 2, 3, 4 )
		//   Range(2, 7, 2) -> ( 2, 4, 6 )
		// **************************************

		var _arr = [];		// Save the array

		// Judge the validity of arguments
		if (_value3 && _value3 * (_value2 - _value1) <= 0) {
			return _arr;		// invaild and return a empty array
		}

		// Default
		var _start = 0;
		var _stop = _value1;
		var _step = _value3 || 1;

		if (typeof(_value2) !== 'undefined') {
			var _start = _value1;
			var _stop = _value2;
		}

		// **************************************************************************
		//   For a positive step, the contents of a range r are determined
		//       by the formula r[i] = start + step*i where i >= 0 and r[i] < stop.
		// **************************************************************************

		if (_step > 0) {
			for (var i = _start; i < _stop; i += _step) {
				_arr.push(i);
			}
		} else {
			for (var i = _start; i > _stop; i += _step) {
				_arr.push(i);
			}
		}

		var range_instance = Immutable_Sequence.return_a_instance(_arr);
		
		return range_instance;
	},
};








///////////////////////////////////////////////////
// --------------------------------------------- //
//                    Testing.                   //
// --------------------------------------------- //
///////////////////////////////////////////////////



// ----------------------  Test1  -----------------------------
var seq1 = Sequence.return_a_instance([0, 1, 2, 5]);
var seq2 = Sequence.return_a_instance([100, 99, 98]);
var seq3 = Sequence.return_a_instance([6]);
var seqNul = Sequence.return_a_instance([[]]);
var seqLong = Sequence.return_a_instance([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
var seqMess = Sequence.return_a_instance([2, 3, 2, 1, 9, 6, 5, 6]);
var seq4 = Sequence.return_a_instance([1, 2, 'x']);
var seq5 = Sequence.return_a_instance([1, 2, 'y']);

var test_list1 = [
	"-------------- Sequence function -------------",
	Sequence.opt_in(2, seq1),	// true
	Sequence.opt_in(seq1, 0),	// true
	Sequence.opt_in(3, seq1),	// false

	Sequence.opt_not_in(3, seq1),	// true
	Sequence.opt_add(seq1, seq2),	// [ 0, 1, 2, 5, 100, 99, 98 ]
	Sequence.opt_len(seq1),		// 4

	Sequence.opt_mul(3, seq1),		// [ 0, 1, 2, 5, 0, 1, 2, 5, 0, 1, 2, 5 ]
	Sequence.opt_mul(seq3, 3),		// [ 6, 6, 6 ]
	Sequence.opt_mul(seqNul, 3),			// [ [], [], [] ]

	Sequence.opt_slice(seqLong, 1, 3),	// [ 1, 2 ]

	Sequence.opt_slice_step(seqLong, 1, 4, 2),	// [ 1, 3 ]
	Sequence.opt_slice_step(seqLong, 1, 4, -1),	// []
	Sequence.opt_slice_step(seqLong, 4, 0, -1),	// [ 4, 3, 2, 1 ]

	Sequence.opt_count(seqLong, 2),	// 1
	Sequence.opt_index(seqLong, 3, 2, 5),	// 3
	Sequence.opt_index(seqLong, 3, 1),		// 3

	Sequence.opt_min(seqMess),		// 1
	Sequence.opt_max(seqMess),		// 9

	Sequence.opt_compare(seq4, seq4),	// 0
	Sequence.opt_compare(seq5, seq4),	// 1
	Sequence.opt_compare(seq4, seq5),	// -1
];





// ----------------------  Test2  -----------------------------
var mseq1 = seq1;
var mseq2 = Mutable_Sequence.return_a_instance([1, 2, 3, 4, 5]);
var mseqMess = seqMess;

var test_list2 = [
	"-------------- Mutable_Sequence function -------------",
	Mutable_Sequence.opt_slice(mseq1, 1, 3),		// [2, 3]
	Mutable_Sequence.opt_slice_get(mseq2, 1, 4),	// [2, 3, 4]
	
	Mutable_Sequence.opt_slice_set(mseqMess, 2, 3, [99, 98]),
	Mutable_Sequence.opt_slice_set(mseq1, 3, 4, 100),
];




// ----------------------  Test3  -----------------------------
var lis1 = mseq1;
var lis2 = mseq2;
var lisMess = mseqMess;

var test_list3 = [
	"-------------- List Sort -------------",
	List.opt_slice(lis1, 1, 3),
	List.opt_slice_get(lis2, 1, 4),
	List.opt_slice_set(lisMess, 2, 3, [99, 98]),
	List.opt_slice_set(lis1, 3, 4, 100),
	List.opt_in(0, lisMess),
	List.opt_in(9, lisMess),
	List.opt_not_in(8, lisMess),
];






// ----------------------  Test4  -----------------------------
var imseq1 = Immutable_Sequence.return_a_instance([9, 8, 7, 6, 5]);
var tup1 = Tuple.return_a_instance([9, 8, 7, 6, 5]);
var tupMess = Tuple.return_a_instance([2, 3, 2, 1, 9, 6, 5, 6, 2]);
var test_list4 = [
	"-------------- Immutable_Sequence and Tuple -------------",
	imseq1.get_value(),
	tup1.get_value(),
	Tuple.opt_in(0, tupMess),
	Tuple.opt_in(9, tupMess),
	Tuple.opt_not_in(8, tupMess),
	Tuple.opt_not_in(6, tupMess),
	Tuple.opt_count(tupMess, 6),
	Tuple.opt_count(tupMess, 2),
];





// ----------------------  Test5  -----------------------------
var test_list5 = [
	"-------------- Range Creation -------------",
	Range.return_a_instance(6),	// [0, 1, 2, 3, 4, 5]
	Range.return_a_instance(1, 10, 2),	// [1, 3, 5, 7, 9]
	Range.return_a_instance(7, 3, -1), 	// [7, 6, 5, 4]
	Range.return_a_instance(1000),	// [0 ... 999]
];



// Display the test result
function disp_test_list(_test_list) {
	for (var i in _test_list) {
		print(_test_list[i]);
	}
}

disp_test_list(test_list5);
