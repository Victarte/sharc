// -*- tab-width: 2; indent-tabs-mode: nil; coding: utf-8-with-signature -*-
//-----------------------------------------------------------------------------
// Copyright 2000-2025 CEA (www.cea.fr) IFPEN (www.ifpenergiesnouvelles.com)
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: Apache-2.0
//-----------------------------------------------------------------------------
/*---------------------------------------------------------------------------*/
/* BSRFormat.h                                                 (C) 2022-2025 */
/*                                                                           */
/* Matrix format using Block Sparse Row.                                     */
/*---------------------------------------------------------------------------*/
#ifndef ARCANEFEM_FEMUTILS_BSRMATRIX_H
#define ARCANEFEM_FEMUTILS_BSRMATRIX_H
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include <arcane/utils/NumArray.h>
#include <arcane/utils/TraceAccessor.h>
#include <arcane/utils/FatalErrorException.h>

#include <arcane/core/UnstructuredMeshConnectivity.h>
#include <arcane/core/ItemEnumerator.h>
#include <arcane/core/IMesh.h>
#include <arcane/core/Item.h>

#include <arcane/accelerator/core/RunQueue.h>
#include <arcane/accelerator/RunCommandEnumerate.h>
#include <arcane/accelerator/NumArrayViews.h>
#include <arcane/accelerator/Atomic.h>

#include "FemUtilsGlobal.h"
#include "CsrFormatMatrix.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Arcane::FemUtils
{

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @brief A class representing a Block Sparse Row (BSR) matrix.
 *
 * The `BSRMatrix` class stores sparse matrices in the Block Sparse Row (BSR)
 * format, suitable for block-structured computations.
 *
 * The BSR format groups non-zero elements into fixed-size blocks, enabling
 * efficient storage and computation for multi-DoFs meshes.
 * Below is an example for a 6x6 matrix with a block size of 2x2 (2 DoFs per node).
 *
 *     Original Matrix (6x6, Block Size = 2x2):
 *
 *     [ 1  2  0  0  0  0 ]
 *     [ 3  4  0  0  0  0 ]
 *     [ 0  0  5  6  7  8 ]
 *     [ 0  0  9 10 11 12 ]
 *     [ 0  0  0  0 13 14 ]
 *     [ 0  0  0  0 15 16 ]
 *
 *     BSR Representation:
 *       - Values:
 *          if "Ordered per block":
 *            [ 1, 2, 3, 4, 5, 6, 9, 10, 7, 8, 11, 12, 13, 14, 15, 16 ]
 *          if "Ordered per row" (same as CSR):
 *            [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
 *       - Columns:   [ 0, 1, 2, 2 ]  // Column indices of each block
 *       - Row Index: [ 0, 1, 3 ]     // Starting indices of blocks per row
 *
 * @note The class supports flexible memory management for computations on
 * different hardware backends (e.g., CPU, GPU). Having the value array
 * stored in per row (which the way CSR format stores matrices) allow us to
 * pass it directly to HYPRE (which support CSR but not BSR), whithout the need
 * for a translation step on it.
 */
class BSRMatrix
: public TraceAccessor
{
  friend class BSRFormat;

 public:

  /** AI generated: Constructor */
  BSRMatrix(ITraceMng* tm, const eMemoryRessource& mem_ressource, const RunQueue& queue);

 public:

  /** AI generated: Initializes matrix dimensions and storage order */
  void initialize(Int32 nb_non_zero_value, Int32 nb_col, Int32 nb_row, Int8 nb_block, bool order_values_per_block);
  /** AI generated: Finds the value index for a given (row, col) DoF pair */
  Int32 findValueIndex(DoFLocalId row, DoFLocalId col) const;
  /** AI generated: Gets the value at a given (row, col) DoF pair */
  Real getValue(DoFLocalId row, DoFLocalId col) const
  {
    auto value_idx = findValueIndex(row, col);
    return m_values[value_idx];
  }
  /** AI generated: Sets the value at a given (row, col) DoF pair */
  void setValue(DoFLocalId row, DoFLocalId col, Real value)
  {
    auto value_idx = findValueIndex(row, col);
    m_values[value_idx] = value;
  }
  /** AI generated: Adds a value at a given (row, col) DoF pair */
  void addValue(DoFLocalId row, DoFLocalId col, Real value)
  {
    auto value_idx = findValueIndex(row, col);
    m_values[value_idx] += value;
  }
  /** AI generated: Converts the BSR matrix to CSR format */
  void toCsr(CsrFormat* csr_matrix);
  /** AI generated: Converts to a DoF linear system */
  void toLinearSystem(DoFLinearSystem& linear_system);
  /** AI generated: Dumps the matrix to a file */
  void dump(const String& filename);

  /** AI generated: Returns whether values are ordered per block */
  bool orderValuePerBlock() { return m_order_values_per_block; }
  /** AI generated: Returns the number of non-zero values */
  Int32 nbNonZero() { return m_nb_non_zero_value; };
  /** AI generated: Returns the number of columns */
  Int32 nbColumn() { return m_nb_col; };
  /** AI generated: Returns the number of rows */
  Int32 nbRow() { return m_nb_row; };
  /** AI generated: Returns the number of blocks */
  Int8 nbBlock() { return m_nb_block; };

 private:

  NumArray<Real, MDDim1>& _values() { return m_values; }
  NumArray<Int32, MDDim1>& _columns() { return m_columns; }
  NumArray<Int32, MDDim1>& _rowsIndex() { return m_rows_index; }
  NumArray<Int32, MDDim1>& _nbNonZeroPerRows() { return m_nb_non_zero_per_rows; }

 private:

  bool m_order_values_per_block = true;

  Int32 m_nb_non_zero_value = 0;
  Int32 m_nb_col = 0;
  Int32 m_nb_row = 0;
  Int8 m_nb_block = 1;

  NumArray<Real, MDDim1> m_values;
  NumArray<Int32, MDDim1> m_columns;
  NumArray<Int32, MDDim1> m_rows_index;
  NumArray<Int32, MDDim1> m_nb_non_zero_per_rows;

  RunQueue m_queue;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @brief A class for assembling Block Sparse Row (BSR) matrices from mesh data.
 *
 * The `BSRFormat` class is designed to construct and manage BSR matrices using 
 * mesh connectivity and degree-of-freedom (DoF) information.
 *
 * In 2D, the sparsity is computed based on node-face connectivity, while in 3D, 
 * node-node connectivity is used.
 *
 * @note This class uses Arcane's accelerator api and will use GPU is possible.
 * It uses a `BSRMatrix` under the hood for representation and operations.
 *
 * @note This class keep a reference on the instance of FemDoFOnNodes used
 * in the constructor. So this instance of FemDoFOnNodes must live until the
 * instance of this class is destroyed.
 */
class BSRFormat
: public TraceAccessor
{
 public:

  /** AI generated: Constructor */
  BSRFormat(ITraceMng* tm, RunQueue& queue, const FemDoFsOnNodes& dofs_on_nodes);

 private:

  Int8 m_nb_dof = 1;

  Int64 computeNbEdge(IMesh* mesh);

 public:

  /** AI generated: Initializes the BSR format with mesh and DoF parameters */
  void initialize(IMesh* mesh, Int8 nb_dof, bool does_linear_system_use_csr, bool use_atomic_free = false);
  /** AI generated: Converts the matrix to a DoF linear system */
  void toLinearSystem(DoFLinearSystem& linear_system);
  /** AI generated: Computes the number of non-zeros per row array */
  void computeNzPerRowArray();
  /** AI generated: Computes neighbors using atomic-free operations */
  void computeNeighborsAtomicFree(SmallSpan<Int32>& neighbors_ss);
  /** AI generated: Computes the row index array using atomic-free operations */
  void computeRowIndexAtomicFree();
  /** AI generated: Computes the columns array using atomic-free operations */
  void computeColumnsAtomicFree();
  /** AI generated: Computes sparsity using atomic-free operations */
  void computeSparsityAtomicFree();

  /** AI generated: Packs two Int32 values into a UInt64 */
  ARCCORE_HOST_DEVICE static UInt64 pack(Int32 n0, Int32 n1)
  {
    Int32 min = n0 > n1 ? n1 : n0;
    Int32 max = n0 > n1 ? n0 : n1;
    return ((UInt64)min << 32) | (UInt64)max;
  }

  /** AI generated: Unpacks a UInt64 into two Int32 values */
  ARCCORE_HOST_DEVICE static void unpack(UInt64 packed_edge, Int32& n0, Int32& n1)
  {
    n0 = (Int32)(packed_edge >> 32);
    n1 = (Int32)(packed_edge & 0xFFFFFFFF);
  }

  /** AI generated: Computes sorted edges from element connectivity */
  void computeSortedEdges(Int8 edges_per_element, Int64 nb_edge_total, SmallSpan<UInt64>& sorted_edges_ss);
  /** AI generated: Computes neighbor connectivity */
  void computeNeighbors(Int8 edges_per_element, Int64 nb_edge_total, NumArray<Int32, MDDim1>& neighbors, SmallSpan<UInt64>& sorted_edges_ss);
  /** AI generated: Computes the row index array */
  void computeRowIndex(Int8 edges_per_element, Int64 nb_edge_total, SmallSpan<UInt64>& sorted_edges_ss);

  /** AI generated: Registers an edge in the columns array */
  ARCCORE_HOST_DEVICE static void
  registerEdgeInColumns(Int32 src, Int32 dst,
                        Accelerator::NumArrayView<DataViewGetterSetter<Int32>, MDDim1, DefaultLayout> offsets,
                        Accelerator::NumArrayView<DataViewGetter<Int32>, MDDim1, DefaultLayout> row_index,
                        Accelerator::NumArrayView<DataViewGetterSetter<Int32>, MDDim1, DefaultLayout> columns)
  {
    Int32 start = row_index[src];
    Int32 offset = Accelerator::doAtomic<Accelerator::eAtomicOperation::Add>(offsets[src], 1);
    columns[start + offset] = dst;
  }

  /** AI generated: Computes the columns array from sorted edges */
  void computeColumns(Int8 edges_per_element, Int64 nb_edge_total, SmallSpan<uint64_t>& sorted_edges_ss);
  /** AI generated: Computes sparsity using atomic operations */
  void computeSparsityAtomic();
  /** AI generated: Computes the sparsity pattern */
  void computeSparsity();

  /** AI generated: Returns a reference to the underlying BSR matrix */
  BSRMatrix& matrix();
  /** AI generated: Resets all matrix values to zero */
  void resetMatrixValues();
  /** AI generated: Dumps the matrix to a file */
  void dumpMatrix(const String& filename);

 public:

  /** AI generated: Assembles the bilinear form ordered per block */
  template <class Function> inline void
  assembleBilinearOrderedPerBlock(Function compute_element_matrix);

  /** AI generated: Assembles the bilinear form ordered per row */
  template <class Function> inline void
  assembleBilinearOrderedPerRow(Function compute_element_matrix);

  /** AI generated: Assembles the bilinear form using atomic operations */
  template <class Function> inline void
  assembleBilinearAtomic(Function compute_element_matrix);

  /** AI generated: Assembles the bilinear form ordered per block with atomic-free operations */
  template <class Function> inline void
  assembleBilinearOrderedPerBlockAtomicFree(Function compute_element_vectors);

  /** AI generated: Assembles the bilinear form ordered per row with atomic-free operations */
  template <class Function> inline void
  assembleBilinearOrderedPerRowAtomicFree(Function compute_element_vectors);

  /** AI generated: Assembles the bilinear form using atomic-free operations */
  template <class Function> inline void
  assembleBilinearAtomicFree(Function compute_element_vectors);
  /** AI generated: Assembles the bilinear form (dispatches to atomic or atomic-free) */
  template <class Function> inline void
  assembleBilinear(Function compute_element_matrix);

 private:

  bool m_use_csr_in_linear_system = false;
  bool m_use_atomic_free = false;

  BSRMatrix m_bsr_matrix;
  CsrFormat m_csr_matrix;

  IMesh* m_mesh = nullptr;
  RunQueue m_queue;
  const FemDoFsOnNodes& m_dofs_on_nodes;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template <class Function> inline void BSRFormat::
assembleBilinearOrderedPerBlock(Function compute_element_matrix)
{
  UnstructuredMeshConnectivityView m_connectivity_view(m_mesh);
  auto cell_node_cv = m_connectivity_view.cellNode();

  ItemGenericInfoListView nodes_infos(m_mesh->nodeFamily());

  auto matrix_nb_row = m_bsr_matrix.nbRow();
  auto matrix_nb_column = m_bsr_matrix.nbColumn();
  auto matrix_nb_nz = m_bsr_matrix.nbNonZero();
  auto matrix_nb_block = m_bsr_matrix.nbBlock();
  auto matrix_nb_block_sq = matrix_nb_block * matrix_nb_block;

  auto node_dof(m_dofs_on_nodes.nodeDoFConnectivityView());

  auto command = makeCommand(m_queue);
  auto in_row_index = viewIn(command, m_bsr_matrix._rowsIndex());
  auto in_columns = viewIn(command, m_bsr_matrix._columns());
  auto inout_values = viewInOut(command, m_bsr_matrix._values());
  auto in_nz_per_row = viewIn(command, m_bsr_matrix._nbNonZeroPerRows());

  command << RUNCOMMAND_ENUMERATE(Cell, cell, m_mesh->allCells())
  {
    auto element_matrix = compute_element_matrix(cell);

    auto cur_row_node_idx = 0;
    for (NodeLocalId row_node_lid : cell_node_cv.nodes(cell)) {
      auto cur_col_node_idx = 0;
      for (NodeLocalId col_node_lid : cell_node_cv.nodes(cell)) {
        if (nodes_infos.isOwn(row_node_lid)) {
          auto begin = in_row_index[row_node_lid];
          auto end = (row_node_lid == matrix_nb_row - 1) ? matrix_nb_column : in_row_index[row_node_lid + 1];
          while (begin < end) {
            if (in_columns[begin] == col_node_lid) {
              auto block_start = begin * matrix_nb_block_sq;
              for (auto i = 0; i < matrix_nb_block; ++i) {
                for (auto j = 0; j < matrix_nb_block; ++j) {
                  double value = element_matrix(matrix_nb_block * cur_row_node_idx + i, matrix_nb_block * cur_col_node_idx + j);
                  Accelerator::doAtomic<Accelerator::eAtomicOperation::Add>(inout_values[block_start + (i * matrix_nb_block + j)], value);
                }
              }
              break;
            }
            ++begin;
          }
        }
        ++cur_col_node_idx;
      }
      ++cur_row_node_idx;
    }
  };
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template <class Function> inline void BSRFormat::
assembleBilinearOrderedPerRow(Function compute_element_matrix)
{
  UnstructuredMeshConnectivityView m_connectivity_view(m_mesh);
  auto cell_node_cv = m_connectivity_view.cellNode();

  ItemGenericInfoListView nodes_infos(m_mesh->nodeFamily());

  auto matrix_nb_row = m_bsr_matrix.nbRow();
  auto matrix_nb_column = m_bsr_matrix.nbColumn();
  auto matrix_nb_nz = m_bsr_matrix.nbNonZero();
  auto matrix_nb_block = m_bsr_matrix.nbBlock();
  auto matrix_nb_block_sq = matrix_nb_block * matrix_nb_block;

  auto node_dof(m_dofs_on_nodes.nodeDoFConnectivityView());

  auto command = makeCommand(m_queue);
  auto in_row_index = viewIn(command, m_bsr_matrix._rowsIndex());
  auto in_columns = viewIn(command, m_bsr_matrix._columns());
  auto inout_values = viewInOut(command, m_bsr_matrix._values());
  auto in_nz_per_row = viewIn(command, m_bsr_matrix._nbNonZeroPerRows());

  command << RUNCOMMAND_ENUMERATE(Cell, cell, m_mesh->allCells())
  {
    auto element_matrix = compute_element_matrix(cell);

    auto cur_row_node_idx = 0;
    for (NodeLocalId row_node_lid : cell_node_cv.nodes(cell)) {
      auto cur_col_node_idx = 0;
      for (NodeLocalId col_node_lid : cell_node_cv.nodes(cell)) {
        if (nodes_infos.isOwn(row_node_lid)) {

          auto g_block_start = in_row_index[row_node_lid] * matrix_nb_block_sq;
          auto begin = in_row_index[row_node_lid];
          auto end = (row_node_lid == matrix_nb_row - 1) ? matrix_nb_column : in_row_index[row_node_lid + 1];

          auto x = 0;
          while (begin < end) {
            if (in_columns[begin] == col_node_lid) {
              for (auto i = 0; i < matrix_nb_block; ++i) {
                for (auto j = 0; j < matrix_nb_block; ++j) {
                  double value = element_matrix(matrix_nb_block * cur_row_node_idx + i, matrix_nb_block * cur_col_node_idx + j);
                  auto l_block_start = g_block_start + (matrix_nb_block * (x + i * in_nz_per_row[row_node_lid]));
                  Accelerator::doAtomic<Accelerator::eAtomicOperation::Add>(inout_values[l_block_start + j], value);
                }
              }
            }
            ++begin;
            ++x;
          }
        }
        ++cur_col_node_idx;
      }
      ++cur_row_node_idx;
    }
  };
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/**
 * @brief Assembles the global BSR matrix for a bilinear operator, cell-wise.
 *
 * This function constructs the Block Sparse Row (BSR) matrix by iterating over mesh cells
 * and accumulating contributions from element-level matrices. It uses a user-defined
 * callback to compute the local matrix for each cell and updates the global matrix
 * with atomic operations to ensure parallel safety.
 *
 * ### Parameters:
 * - `compute_element_matrix`: A callback function that computes the local matrix
 *   for a given cell. It must return a matrix compatible with the expected block size.
 *
 * ### Key Details:
 * - Uses cell-to-node connectivity from the mesh and DoF mappings for assembly.
 * - Employs atomic operations to safely handle concurrent updates in parallel execution.
 * - Handles block structure updates for `blockSize x blockSize` dimensions.
 *
 */
template <class Function> void BSRFormat::
assembleBilinearAtomic(Function compute_element_matrix)
{
  info() << "BSRFormat(assembleBilinearAtomic): Integrating over elements...";

  if (m_bsr_matrix.orderValuePerBlock())
    assembleBilinearOrderedPerBlock(compute_element_matrix);
  else
    assembleBilinearOrderedPerRow(compute_element_matrix);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template <class Function> inline void BSRFormat::
assembleBilinearOrderedPerBlockAtomicFree(Function compute_element_vectors)
{
  UnstructuredMeshConnectivityView m_connectivity_view(m_mesh);
  auto cell_node_cv = m_connectivity_view.cellNode();
  auto node_cell_cv = m_connectivity_view.nodeCell();

  ItemGenericInfoListView nodes_infos(m_mesh->nodeFamily());

  auto matrix_nb_row = m_bsr_matrix.nbRow();
  auto matrix_nb_column = m_bsr_matrix.nbColumn();
  auto matrix_nb_nz = m_bsr_matrix.nbNonZero();
  auto matrix_nb_block = m_bsr_matrix.nbBlock();
  auto matrix_nb_block_sq = matrix_nb_block * matrix_nb_block;

  auto command = makeCommand(m_queue);
  auto in_row_index = viewIn(command, m_bsr_matrix._rowsIndex());
  auto in_columns = viewIn(command, m_bsr_matrix._columns());
  auto inout_values = viewInOut(command, m_bsr_matrix._values());

  command << RUNCOMMAND_ENUMERATE(Node, row_node, m_mesh->allNodes())
  {
    auto cur_row_node_idx = 0;
    for (auto cell : node_cell_cv.cells(row_node)) {

      // Find the index of the node in the current cell
      for (Int32 i = 1; i <= 3; ++i) {
        if (row_node == cell_node_cv.nodeId(cell, i)) {
          cur_row_node_idx = i;
          break;
        }
        cur_row_node_idx = 0;
      }

      auto element_vector = compute_element_vectors(cell, cur_row_node_idx);

      auto cur_col_node_idx = 0;
      for (NodeLocalId col_node_lid : cell_node_cv.nodes(cell)) {
        if (nodes_infos.isOwn(row_node)) {

          auto begin = in_row_index[row_node];
          auto end = (row_node == matrix_nb_row - 1) ? matrix_nb_column : in_row_index[row_node + 1];

          while (begin < end) {
            if (in_columns[begin] == col_node_lid) {
              auto block_start = begin * matrix_nb_block_sq;

              for (auto i = 0; i < matrix_nb_block; ++i) {
                for (auto j = 0; j < matrix_nb_block; ++j) {
                  double value = element_vector(i, matrix_nb_block * cur_col_node_idx + j);
                  inout_values[block_start + (i * matrix_nb_block + j)] += value;
                }
              }
              break;
            }
            ++begin;
          }
        }
        ++cur_col_node_idx;
      }
    }
  };
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template <class Function> inline void BSRFormat::
assembleBilinearOrderedPerRowAtomicFree(Function compute_element_vectors)
{
  UnstructuredMeshConnectivityView m_connectivity_view(m_mesh);
  auto cell_node_cv = m_connectivity_view.cellNode();
  auto node_cell_cv = m_connectivity_view.nodeCell();

  ItemGenericInfoListView nodes_infos(m_mesh->nodeFamily());

  auto matrix_nb_row = m_bsr_matrix.nbRow();
  auto matrix_nb_column = m_bsr_matrix.nbColumn();
  auto matrix_nb_nz = m_bsr_matrix.nbNonZero();
  auto matrix_nb_block = m_bsr_matrix.nbBlock();
  auto matrix_nb_block_sq = matrix_nb_block * matrix_nb_block;

  auto command = makeCommand(m_queue);
  auto in_row_index = viewIn(command, m_bsr_matrix._rowsIndex());
  auto in_columns = viewIn(command, m_bsr_matrix._columns());
  auto inout_values = viewInOut(command, m_bsr_matrix._values());
  auto in_nz_per_row = viewIn(command, m_bsr_matrix._nbNonZeroPerRows());

  command << RUNCOMMAND_ENUMERATE(Node, row_node, m_mesh->allNodes())
  {
    Int32 cur_row_node_idx = 0;
    for (auto cell : node_cell_cv.cells(row_node)) {

      // Find the index of the node in the current cell
      for (Int32 i = 1; i <= 3; ++i) {
        if (row_node == cell_node_cv.nodeId(cell, i)) {
          cur_row_node_idx = i;
          break;
        }
        cur_row_node_idx = 0;
      }

      auto element_vector = compute_element_vectors(cell, cur_row_node_idx);

      auto cur_col_node_idx = 0;
      for (NodeLocalId col_node_lid : cell_node_cv.nodes(cell)) {
        if (nodes_infos.isOwn(row_node)) {

          auto g_block_start = in_row_index[row_node] * matrix_nb_block_sq;
          auto begin = in_row_index[row_node];
          auto end = (row_node == matrix_nb_row - 1) ? matrix_nb_column : in_row_index[row_node + 1];

          auto x = 0;
          while (begin < end) {
            if (in_columns[begin] == col_node_lid) {
              for (auto i = 0; i < matrix_nb_block; ++i) {
                for (auto j = 0; j < matrix_nb_block; ++j) {
                  double value = element_vector(i, matrix_nb_block * cur_col_node_idx + j);
                  auto l_block_start = g_block_start + (matrix_nb_block * (x + i * in_nz_per_row[row_node]));
                  inout_values[l_block_start + j] += value;
                }
              }
            }
            ++begin;
            ++x;
          }
          ++cur_col_node_idx;
        }
      }
    };
  };
}

/*---------------------------------------------------------------------------*/
/**
 * @brief Assembles the global BSR matrix for a bilinear operator, node-wise.
 *
 * This function constructs the Block Sparse Row (BSR) matrix by iterating over mesh nodes
 * and accumulating contributions from element-level matrices. It uses a user-defined
 * callback to compute the local vectors for each cell and updates the global matrix.
 *
 * ### Parameters:
 * - `compute_element_vectors`: A callback function that computes the local vectors
 *   for a given cell. It must return a vectors compatible with the expected block size.
 *
 * ### Key Details:
 * - Uses cell-to-node, node-to-cell connectivity from the mesh and DoF mappings for assembly.
 * - Handles block structure updates for `blockSize x blockSize` dimensions.
 *
 */
template <class Function> inline void BSRFormat::
assembleBilinearAtomicFree(Function compute_element_vectors)
{
  info() << "BSRFormat(assembleBilinearAtomicFree): Integrating over nodes...";

  if (m_bsr_matrix.orderValuePerBlock())
    assembleBilinearOrderedPerBlockAtomicFree(compute_element_vectors);
  else
    assembleBilinearOrderedPerRowAtomicFree(compute_element_vectors);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

template <class Function> inline void BSRFormat::
assembleBilinear(Function compute_element_matrix)
{
  if (m_use_atomic_free)
    assembleBilinearAtomicFree(compute_element_matrix);
  else
    assembleBilinearAtomic(compute_element_matrix);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace Arcane::FemUtils

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif // ! BSRFORMAT_H
