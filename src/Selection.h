#pragma once

#include <memory>
#include <pxr/usd/sdf/layer.h>
#include <pxr/usd/sdf/path.h>

PXR_NAMESPACE_USING_DIRECTIVE

/// A hash type used to track changes in selection state
using SelectionHash = std::size_t;

/// \class Selection
/// \brief Manages selection state for USD layers and stages.
///
/// This API is designed to support selection operations in a UI or editor context.
/// It abstracts over the specifics of USD types (SdfLayer, UsdStage) and handles
/// both prim and property selection. The interface is templated to support both layers
/// and stages as selection "owners".
struct Selection {
    Selection();
    ~Selection();

    /// \brief Clear all selections for a given owner (layer or stage).
    /// \tparam OwnerT Can be SdfLayerRefPtr, TfWeakPtr<SdfLayer>, UsdStageRefPtr, etc.
    /// \param owner The layer or stage whose selection is being cleared.
    template <typename OwnerT> void Clear(const OwnerT &owner);

    /// \brief Add a single selected item to the selection domain of the owner.
    /// \param owner The layer or stage where the selection applies.
    /// \param path The path of the item to select.
    template <typename OwnerT> void AddSelected(const OwnerT &owner, const SdfPath &path);

    /// \brief Remove a selected item from the owner’s selection.
    /// \note Not implemented for all types.
    template <typename OwnerT> void RemoveSelected(const OwnerT &owner, const SdfPath &path);

    /// \brief Replace current selection with a new single item.
    /// \param owner The layer or stage.
    /// \param path The item to be selected exclusively.
    template <typename OwnerT> void SetSelected(const OwnerT &owner, const SdfPath &path);

    /// \brief Check if the selection is empty for a given owner.
    template <typename OwnerT> bool IsSelectionEmpty(const OwnerT &owner) const;

    /// \brief Check if a specific path is selected in the given owner.
    template <typename OwnerT> bool IsSelected(const OwnerT &owner, const SdfPath &path) const;

    /// \brief Check whether a given SdfPrimSpec or SdfAttributeSpec is selected.
    /// \note This is only valid for items already known to belong to the currently active layer.
    /// Ownership context is inferred from the stored selection domains.
    ///
    /// Prefer using IsSelected(owner, path) when working at the path level.
    template <typename ItemT> bool IsSelected(const ItemT &item) const;

    /// \brief Update and compare the selection hash to detect changes.
    /// \returns true if the selection has changed since the last hash.
    template <typename OwnerT> bool UpdateSelectionHash(const OwnerT &owner, SelectionHash &lastSelectionHash);

    /// \brief Return one selected prim path, typically used as a reference or "anchor" for UI actions.
    /// For stages: this is usually the first selected prim in the order reported by HdSelection.
    /// For layers: this is an arbitrary selected prim path (unordered).
    template <typename OwnerT> SdfPath GetAnchorPrimPath(const OwnerT &owner) const;

    /// \brief Return one selected property path, if any exist.
    /// For layers: this is an arbitrary selected property path (unordered).
    template <typename OwnerT> SdfPath GetAnchorPropertyPath(const OwnerT &owner) const;

    /// \brief Retrieve all selected paths in the owner.
    template <typename OwnerT> std::vector<SdfPath> GetSelectedPaths(const OwnerT &owner) const;

    /// \brief Internal selection data structure. Not meant to be accessed directly.
    struct SelectionData;
    SelectionData *_data;
};
