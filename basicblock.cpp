#include "binaryninjaapi.h"

using namespace BinaryNinja;
using namespace std;


BasicBlock::BasicBlock(BNBasicBlock* block): m_block(block)
{
}


BasicBlock::~BasicBlock()
{
	BNFreeBasicBlock(m_block);
}


Ref<Function> BasicBlock::GetFunction() const
{
	return new Function(BNGetBasicBlockFunction(m_block));
}


Ref<Architecture> BasicBlock::GetArchitecture() const
{
	return new CoreArchitecture(BNGetBasicBlockArchitecture(m_block));
}


uint64_t BasicBlock::GetStart() const
{
	return BNGetBasicBlockStart(m_block);
}


uint64_t BasicBlock::GetEnd() const
{
	return BNGetBasicBlockEnd(m_block);
}


uint64_t BasicBlock::GetLength() const
{
	return BNGetBasicBlockLength(m_block);
}


vector<uint8_t> BasicBlock::GetInstructionSizes() const
{
	size_t count;
	uint8_t* array = BNGetBasicBlockInstructionSizes(m_block, &count);

	vector<uint8_t> result;
	result.insert(result.end(), &array[0], &array[count]);

	BNFreeBasicBlockInstructionSizeList(array);
	return result;
}


vector<BNBasicBlockEdge> BasicBlock::GetOutgoingEdges() const
{
	size_t count;
	BNBasicBlockEdge* array = BNGetBasicBlockOutgoingEdges(m_block, &count);

	vector<BNBasicBlockEdge> result;
	for (size_t i = 0; i < count; i++)
		result.push_back(array[i]);

	BNFreeBasicBlockOutgoingEdgeList(array);
	return result;
}