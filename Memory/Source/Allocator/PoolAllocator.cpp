#include"IAllocator.h"

namespace VIMemory {
	PoolAllocator::PoolAllocator(size_t memoryCapacity, const void* startAddress, size_t chunkSize, uint8_t chunkAligment) : 
		IAllocator(memoryCapacity, startAddress), mChunkSize(chunkSize), mChunkAlignment(chunkAligment), mFreelistHead() 
	{
		union {
			void* asVoidPtr;
			uintptr_t asUintPtr;
		};

		asVoidPtr = const_cast<void*>(mStartAddress);
		// Reset memory address to follow the chunk alignment
		uintptr_t startAddressAfterAligned = IAllocator::AlignForward(asUintPtr, static_cast<uintptr_t>(mChunkAlignment));
		size_t memoryDifferent = static_cast<size_t>(startAddressAfterAligned - asUintPtr);
		mMemorySize -= memoryDifferent;

		mChunkSize = IAllocator::AlignForward(mChunkSize, mChunkAlignment);
		assert(mChunkSize >= sizeof(PoolFreeNode) && "Invalid memory chunk size");
		assert(mMemorySize > mChunkSize && "Invalid memory size");
		mFreelistHead = nullptr;

		Clear();
	}

	PoolAllocator::~PoolAllocator() {

	}

	void* PoolAllocator::AllocateChunk() {
		PoolFreeNode* node = mFreelistHead;
		assert(node != nullptr && "Head free node is null");
		mFreelistHead = node->Next;

		mUsedMemory += mChunkSize;
		mAllocationCount++;
		
		return memset(node, 0, mChunkSize);
	}

	void* PoolAllocator::Allocate(size_t size) {
		assert(false && "Not supported method for Pool Allocator");
		return nullptr;
	}

	void PoolAllocator::Free(void* memory) {
		union {
			void* asVoidPtr;
			char* asCharPtr;
		};
		asVoidPtr = const_cast<void*>(mStartAddress);

		void* endAddress = &asCharPtr[mMemorySize];
		if (memory >= endAddress || memory < asVoidPtr) {
			return;
		}

		if (memory == nullptr) {
			return;
		}

		PoolFreeNode* node = reinterpret_cast<PoolFreeNode*>(memory);
		node->Next = mFreelistHead;
		mFreelistHead = node;

		mUsedMemory -= mChunkSize;
		mAllocationCount--;
	}

	void PoolAllocator::Clear() {
		size_t numberOfChunks = mMemorySize / mChunkSize;

		union {
			void* asVoidPtr;
			char* asCharPtr;
		};

		asVoidPtr = const_cast<void*>(mStartAddress);

		for (size_t idx = 0; idx < numberOfChunks; idx++) {
			PoolFreeNode* chunk = reinterpret_cast<PoolFreeNode*>(&asCharPtr[idx * mChunkSize]);
			// Push chunk to the head of the free list
			chunk->Next = mFreelistHead;
			mFreelistHead = chunk;
		}
	}
}