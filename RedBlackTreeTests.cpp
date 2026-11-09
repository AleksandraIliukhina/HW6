
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"
#include <stdexcept>

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	assert(rbt.ToPrefixString() == " B15 ");

	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
`	// Aleksandra: right right case
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(15);
	rbt->Insert(20);
	assert(rbt->ToPrefixString() == " B15  R10  R20 ");
	delete rbt;

	// left right case
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(10);
	rbt->Insert(20);
	assert(rbt->ToPrefixString() == " B20  R10  R30 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
    cout << "Testing Insert Fourth Node..." << endl;
    RedBlackTree rbt;

    rbt.Insert(20);
    rbt.Insert(10);
    rbt.Insert(30);
    rbt.Insert(5);

    // The red uncle causes recoloring
    assert(rbt.ToPrefixString() == " B20  B10  R5  R30 ");

    cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	// Aleksandra: check that all five nodes were inserted
	RedBlackTree *rbt2 = new RedBlackTree();
	rbt2->Insert(30);
	rbt2->Insert(15);
	rbt2->Insert(45);
	rbt2->Insert(10);
	rbt2->Insert(25);

	assert(rbt2->Size() == 5);
	assert(rbt2->Contains(30));
	assert(rbt2->Contains(15));
	assert(rbt2->Contains(45));
	assert(rbt2->Contains(10));
	assert(rbt2->Contains(25));
	delete rbt2;
	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}

void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);

	// Aleksandra: check values that exist in the tree
	assert(rbt->Contains(40));
	assert(rbt->Contains(22));
	assert(rbt->Contains(15));
	assert(rbt->Contains(31));
	assert(rbt->Contains(55));
	assert(rbt->Contains(12));
	assert(rbt->Contains(17));
	assert(rbt->Contains(29));
	assert(rbt->Contains(34));
	// Check values that do not exist in the tree
	assert(!rbt->Contains(100));
	assert(!rbt->Contains(0));
	assert(!rbt->Contains(25));
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestGetMinimumMaximum(){
    cout << "Testing Get Minimum and Get Maximum..." << endl;
    RedBlackTree rbt;

    // Test an empty tree.
    assert(rbt.Size() == 0);
    // Insert several values.
    rbt.Insert(40);
    rbt.Insert(22);
    rbt.Insert(15);
    rbt.Insert(31);
    rbt.Insert(55);
    rbt.Insert(12);
    rbt.Insert(17);
    // Check the number of elements.
    assert(rbt.Size() == 7);
    // Check minimum and maximum values.
    assert(rbt.GetMin() == 12);
    assert(rbt.GetMax() == 55);

    cout << "PASSED!" << endl << endl;
}

void TestDuplicateInsertion(){
    cout << "Testing Duplicate Insertion..." << endl;
    RedBlackTree rbt;

    rbt.Insert(10);
    rbt.Insert(20);

    bool exceptionThrown = false;

    try{
        rbt.Insert(10);
    }catch(const invalid_argument&){
        exceptionThrown = true;
    }

    assert(exceptionThrown);
    // The tree should still contain only two nodes.
    assert(rbt.Size() == 2);

    cout << "PASSED!" << endl << endl;
}


void TestPrivateTests(){
    cout << "Testing private methods..." << endl;
    RedBlackTree rbt;
    rbt.PrivateTests();
    cout << "PASSED!" << endl << endl;
}


int main(){
	TestSimpleConstructor();
	TestConstructor();
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();

	// Aleksandra: for the tests I made.
	TestPrivateTests();
	// Aleksandra: to test duplicate insertion.
	TestDuplicateInsertion();
	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
