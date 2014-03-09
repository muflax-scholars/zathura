/* See LICENSE file for license and copyright information */

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <stdbool.h>
#include <girara/types.h>

#include "types.h"

/**
 * Open the document
 *
 * @param plugin_manager The plugin manager
 * @param path Path to the document
 * @param password Password of the document or NULL
 * @param error Optional error parameter
 * @return The document object and NULL if an error occurs
 */
zathura_document_t* zathura_document_open(zathura_plugin_manager_t*
    plugin_manager, const char* path, const char* password, zathura_error_t*
    error);

/**
 * Free the document
 *
 * @param document
 * @return ZATHURA_ERROR_OK when no error occured, otherwise see
 *    zathura_error_t
 */
zathura_error_t zathura_document_free(zathura_document_t* document);

/**
 * Returns the path of the document
 *
 * @param document The document
 * @return The file path of the document
 */
const char* zathura_document_get_path(zathura_document_t* document);

/**
 * Returns the basename of the document
 *
 * @param document The document
 * @return The basename of the document
 */
const char* zathura_document_get_basename(zathura_document_t* document);

/**
 * Returns the original path of the document
 *
 * @param document The document
 * @return The original file path of the document
 */
const char* zathura_document_get_orig_path(zathura_document_t* document);

/**
 * Returns the original basename of the document
 *
 * @param document The document
 * @return The original basename of the document
 */
const char* zathura_document_get_orig_basename(zathura_document_t* document);

/**
 * Returns the password of the document
 *
 * @param document The document
 * @return Returns the password of the document
 */
const char* zathura_document_get_password(zathura_document_t* document);

/**
 * Returns the page at the given index
 *
 * @param document The document
 * @param index The index of the page
 * @return The page or NULL if an error occured
 */
zathura_page_t* zathura_document_get_page(zathura_document_t* document, unsigned int index);

/**
 * Returns the number of pages
 *
 * @param document The document
 * @return Number of pages
 */
unsigned int zathura_document_get_number_of_pages(zathura_document_t* document);

/**
 * Sets the number of pages
 *
 * @param document The document
 * @param number_of_pages Number of pages
 */
void zathura_document_set_number_of_pages(zathura_document_t* document, unsigned
    int number_of_pages);

/**
 * Returns the current page number
 *
 * @param document The document
 * @return Current page
 */
unsigned int zathura_document_get_current_page_number(zathura_document_t* document);

/**
 * Sets the number of pages
 *
 * @param document The document
 * @param current_page The current page number
 */
void zathura_document_set_current_page_number(zathura_document_t* document, unsigned
    int current_page);

/**
 * Returns the X position, as a value relative to the document width (0=left,
 * 1=right).
 *
 * @param document The document
 * @return X adjustment
 */
double zathura_document_get_position_x(zathura_document_t* document);

/**
 * Returns the Y position as value relative to the document height (0=top,
 * 1=bottom)
 *
 * @param document The document
 * @return Y adjustment
 */
double zathura_document_get_position_y(zathura_document_t* document);

/**
 * Sets the X position as a value relative to the document width (0=left,
 * 1=right)
 *
 * @param document The document
 * @param position_x the X adjustment
 */
void zathura_document_set_position_x(zathura_document_t* document, double position_x);

/**
 * Sets the Y position as a value relative to the document height (0=top,
 * 1=bottom)
 *
 * @param document The document
 * @param position_y the Y adjustment
 */
void zathura_document_set_position_y(zathura_document_t* document, double position_y);

/**
 * Returns the current scale value of the document
 *
 * @param document The document
 * @return The current scale value
 */
double zathura_document_get_scale(zathura_document_t* document);

/**
 * Sets the new scale value of the document
 *
 * @param document The document
 * @param scale The new scale value
 */
void zathura_document_set_scale(zathura_document_t* document, double scale);

/**
 * Returns the rotation value of zathura (0..360)
 *
 * @param document The document
 * @return The current rotation value
 */
unsigned int zathura_document_get_rotation(zathura_document_t* document);

/**
 * Sets the new rotation value
 *
 * @param document The document
 * @param rotation The new rotation value
 */
void zathura_document_set_rotation(zathura_document_t* document, unsigned int rotation);

/**
 * Returns the adjust mode of the document
 *
 * @param document The document
 * @return The adjust mode
 */
zathura_adjust_mode_t zathura_document_get_adjust_mode(zathura_document_t* document);

/**
 * Sets the new adjust mode of the document
 *
 * @param document The document
 * @param mode The new adjust mode
 */
void zathura_document_set_adjust_mode(zathura_document_t* document, zathura_adjust_mode_t mode);

/**
 * Returns the page offset of the document
 *
 * @param document The document
 * @return The page offset
 */
int zathura_document_get_page_offset(zathura_document_t* document);

/**
 * Sets the new page offset of the document
 *
 * @param document The document
 * @param page_offset The new page offset
 */
void zathura_document_set_page_offset(zathura_document_t* document, unsigned int page_offset);

/**
 * Returns the private data of the document
 *
 * @param document The document
 * @return The private data or NULL
 */
void* zathura_document_get_data(zathura_document_t* document);

/**
 * Sets the private data of the document
 *
 * @param document The document
 * @param data The new private data
 */
void zathura_document_set_data(zathura_document_t* document, void* data);

/**
 * Sets the width of the viewport in pixels.
 *
 * @param[in] document     The document instance
 * @param[in] width        The width of the viewport
 */
void
zathura_document_set_viewport_width(zathura_document_t* document, unsigned int width);

/**
 * Sets the height of the viewport in pixels.
 *
 * @param[in] document     The document instance
 * @param[in] height       The height of the viewport
 */
void
zathura_document_set_viewport_height(zathura_document_t* document, unsigned int height);

/**
 * Return the size of the viewport in pixels.
 *
 * @param[in]  document     The document instance
 * @param[out] height,width The width and height of the viewport
 */
void
zathura_document_get_viewport_size(zathura_document_t* document,
                                   unsigned int *height, unsigned int* width);

/**
 * Return the size of a cell from the document's layout table in pixels. Assumes
 * that the table is homogeneous (i.e. every cell has the same dimensions). It
 * takes the current scale into account.
 *
 * @param[in]  document     The document instance
 * @param[out] height,width The computed height and width of the cell
 */
void zathura_document_get_cell_size(zathura_document_t* document,
                                    unsigned int* height, unsigned int* width);

/**
 * Compute the size of the entire document to be displayed in pixels. Takes into
 * account the scale, the layout of the pages, and the padding between them. It
 * should be equal to the allocation of zathura->ui.page_widget once it's shown.
 *
 * @param[in]  document               The document
 * @param[out] height,width           The height and width of the document
 */
void zathura_document_get_document_size(zathura_document_t* document,
                                        unsigned int* height, unsigned int* width);

/**
 * Sets the layout of the pages in the document
 *
 * @param[in]  document          The document instance
 * @param[in]  page_padding      pixels of padding between pages
 * @param[in]  pages_per_row     number of pages per row
 * @param[in]  first_page_column column of the first page (first column is 1)
 */
void zathura_document_set_page_layout(zathura_document_t* document, unsigned int page_padding,
                                      unsigned int pages_per_row, unsigned int first_page_column);

/**
 * Returns the padding in pixels betwen pages
 *
 * @param document The document
 * @return The padding in pixels between pages
 */
unsigned int zathura_document_get_page_padding(zathura_document_t* document);

/**
 * Returns the number of pages per row
 *
 * @param document The document
 * @return The number of pages per row
 */
unsigned int zathura_document_get_pages_per_row(zathura_document_t* document);

/**
 * Returns the column for the first page (first column = 1)
 *
 * @param document The document
 * @return The column for the first page
 */
unsigned int zathura_document_get_first_page_column(zathura_document_t* document);

/**
 * Save the document
 *
 * @param document The document object
 * @param path Path for the saved file
 * @return ZATHURA_ERROR_OK when no error occured, otherwise see
 *    zathura_error_t
 */
zathura_error_t zathura_document_save_as(zathura_document_t* document, const char* path);

/**
 * Generate the document index
 *
 * @param document The document object
 * @param error Set to an error value (see \ref zathura_error_t) if an
 *   error occured
 * @return Generated index
 */

girara_tree_node_t* zathura_document_index_generate(zathura_document_t* document, zathura_error_t* error);

/**
 * Get list of attachments
 *
 * @param document The document object
 * @param error Set to an error value (see \ref zathura_error_t) if an
 *   error occured
 * @return List of attachments
 */
girara_list_t* zathura_document_attachments_get(zathura_document_t* document, zathura_error_t* error);

/**
 * Save document attachment
 *
 * @param document The document objects
 * @param attachment name of the attachment
 * @param file the target filename
 * @return ZATHURA_ERROR_OK when no error occured, otherwise see
 *    zathura_error_t
 */
zathura_error_t zathura_document_attachment_save(zathura_document_t* document, const char* attachment, const char* file);

/**
 * Returns a string of the requested information
 *
 * @param document The zathura document
 * @param error Set to an error value (see \ref zathura_error_t) if an
 *   error occured
 * @return List of document information entries or NULL if information could not be retreived
 */
girara_list_t* zathura_document_get_information(zathura_document_t* document, zathura_error_t* error);

#endif // DOCUMENT_H
