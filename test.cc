
#include <gtest/gtest.h>
#include "clause.h"

TEST(LiteralTest, UnassignedLiteral)
{
    simplesat::literal l;
    ASSERT_EQ(l.get_state(), -1);
}

TEST(LiteralTest, AssignedLiteral)
{
    simplesat::literal l;
    l.assign(true);
    ASSERT_EQ(l.get_state(), 1);
}

TEST(LiteralTest, UnassignedLiteralValue)
{
    simplesat::literal l;
    l.assign(false);
    ASSERT_EQ(l.get_state(), 0);
    l.unassign();
    ASSERT_EQ(l.get_state(), -1);
}

TEST(LiteralTest, AssignedLiteralValue)
{
    simplesat::literal l;
    l.assign(true);
    ASSERT_EQ(l.get_state(), 1);
    l.assign(false);
    ASSERT_EQ(l.get_state(), 0);
}

TEST(ClauseTest, EmptyClause)
{
    simplesat::clause c;
    ASSERT_EQ(c.val(), 1);
}

TEST(ClauseTest, SatisfiedClause)
{
    simplesat::clause c;
    simplesat::literal l1;
    simplesat::literal l2;
    l1.assign(true);
    c.add_literal(&l1);
    c.add_literal(&l2);
    ASSERT_EQ(c.val(), 1);
}

TEST(ClauseTest, NotSureClause)
{
    simplesat::clause c;
    simplesat::literal l1;
    simplesat::literal l2;
    c.add_literal(&l1);
    c.add_literal(&l2);
    ASSERT_EQ(c.val(), 0);
    l2.assign(false);
    ASSERT_EQ(c.val(), 0);
}

TEST(ClauseTest, ClauseWithNeg)
{
    simplesat::clause c;
    simplesat::literal l1;
    simplesat::literal l2;
    c.add_literal(&l1, true);
    c.add_literal(&l2);
    ASSERT_EQ(c.val(), 0);
    l1.assign(false);
    ASSERT_EQ(c.val(), 1);
}


TEST(ClauseTest, UnsatisfiedClause)
{
    simplesat::clause c;
    simplesat::literal l1;
    simplesat::literal l2;
    l1.assign(false);
    c.add_literal(&l1);
    c.add_literal(&l2);
    ASSERT_EQ(c.val(), 0);
    l2.assign(false);
    ASSERT_EQ(c.val(), -1);
}

TEST(ClauseTest, GetSingleUnknownLiteral)
{
    simplesat::clause c;
    simplesat::literal l1;
    simplesat::literal l2;
    simplesat::literal l3;
    c.add_literal(&l1);
    c.add_literal(&l2, true);
    c.add_literal(&l3);
    ASSERT_EQ(c.val(), 0);
    l1.assign(false);
    ASSERT_EQ(c.val(), 0);
    auto x = c.get_single_unknown_literal();
    ASSERT_EQ(x.first, nullptr);
    ASSERT_EQ(x.second, false);
    l3.assign(true);
    ASSERT_EQ(c.val(), 1);
    x = c.get_single_unknown_literal();
    ASSERT_EQ(x.first, &l2);
    ASSERT_EQ(x.second, true);
    l3.assign(false);
    ASSERT_EQ(c.val(), 0);
    x = c.get_single_unknown_literal();
    ASSERT_EQ(x.first, &l2);
    ASSERT_EQ(x.second, true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}