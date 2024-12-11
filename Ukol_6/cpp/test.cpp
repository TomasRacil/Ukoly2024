#include "gtest/gtest.h"
#include "hanoi.cpp"

// Custom equality comparer for Tah structs
bool jsouTahyRovny(const Tah &a, const Tah &b)
{
    return a.disk == b.disk && a.z == b.z && a.na == b.na && a.stavVezi == b.stavVezi;
}

TEST(HanoiTest, JedenDisk)
{
    vector<vector<int>> veze(3);
    veze[0].push_back(1);
    vector<Tah> tahy;
    hanoi(1, 'A', 'B', 'C', veze, tahy);

    vector<Tah> ocekavaneTahy = {{1, 'A', 'C', {{}, {}, {1}}}};
    ASSERT_EQ(tahy.size(), ocekavaneTahy.size()); // Check sizes first for better error messages
    for (size_t i = 0; i < tahy.size(); ++i)
    {
        ASSERT_TRUE(jsouTahyRovny(tahy[i], ocekavaneTahy[i])) << "Tahs are not equal at index: " << i;
    }
}

TEST(HanoiTest, DvaDisky)
{
    vector<vector<int>> veze(3);
    veze[0].push_back(2);
    veze[0].push_back(1);
    vector<Tah> tahy;
    hanoi(2, 'A', 'B', 'C', veze, tahy);

    vector<Tah> ocekavaneTahy = {
        {1, 'A', 'B', {{2}, {1}, {}}},
        {2, 'A', 'C', {{}, {1}, {2}}},
        {1, 'B', 'C', {{}, {}, {2, 1}}}};
    ASSERT_EQ(tahy.size(), ocekavaneTahy.size()); // Check sizes first for better error messages
    for (size_t i = 0; i < tahy.size(); ++i)
    {
        ASSERT_TRUE(jsouTahyRovny(tahy[i], ocekavaneTahy[i])) << "Tahs are not equal at index: " << i;
    }
}

TEST(HanoiTest, TriDisky)
{
    vector<vector<int>> veze(3);
    veze[0].push_back(3);
    veze[0].push_back(2);
    veze[0].push_back(1);
    vector<Tah> tahy;
    hanoi(3, 'A', 'B', 'C', veze, tahy);

    vector<Tah> ocekavaneTahy = {
        {1, 'A', 'C', {{3, 2}, {}, {1}}},
        {2, 'A', 'B', {{3}, {2}, {1}}},
        {1, 'C', 'B', {{3}, {2, 1}, {}}},
        {3, 'A', 'C', {{}, {2, 1}, {3}}},
        {1, 'B', 'A', {{1}, {2}, {3}}},
        {2, 'B', 'C', {{1}, {}, {3, 2}}},
        {1, 'A', 'C', {{}, {}, {3, 2, 1}}}};
    ASSERT_EQ(tahy.size(), ocekavaneTahy.size()); // Check sizes first for better error messages
    for (size_t i = 0; i < tahy.size(); ++i)
    {
        ASSERT_TRUE(jsouTahyRovny(tahy[i], ocekavaneTahy[i])) << "Tahs are not equal at index: " << i;
    }
}
TEST(HanoiTest, InvalidNumberOfDisks)
{
    vector<vector<int>> veze(3); // Initialize towers
    vector<Tah> tahy;            // Initialize moves

    // Test with zero disks
    ASSERT_NO_THROW({ hanoi(0, 'A', 'B', 'C', veze, tahy); }); // Should not throw
    ASSERT_EQ(tahy.size(), 0) << "Expected zero moves for zero disks";

    // Test with negative disks
    ASSERT_NO_THROW({ hanoi(-1, 'A', 'B', 'C', veze, tahy); }); // Should not throw
    ASSERT_EQ(tahy.size(), 0) << "Expected zero moves for negative disks";

    // Test with a valid number of disks
    hanoi(1, 'A', 'B', 'C', veze, tahy);
    ASSERT_EQ(tahy.size(), 1);
}
