
#include <gtest/gtest.h>
#include "clause.h"

TEST(ClauseTest, EmptyClause)
{
    simplesat::clause c;
    ASSERT_EQ(c.val(), -1);
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}