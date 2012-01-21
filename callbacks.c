/* See LICENSE file for license and copyright information */

#include <girara/statusbar.h>
#include <girara/session.h>
#include <girara/settings.h>
#include <girara/utils.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "zathura.h"
#include "render.h"
#include "document.h"
#include "utils.h"
#include "shortcuts.h"

gboolean
cb_destroy(GtkWidget* UNUSED(widget), gpointer UNUSED(data))
{
  gtk_main_quit();
  return TRUE;
}

void
buffer_changed(girara_session_t* session)
{
  g_return_if_fail(session != NULL);
  g_return_if_fail(session->global.data != NULL);

  zathura_t* zathura = session->global.data;

  char* buffer = girara_buffer_get(session);

  if (buffer) {
    girara_statusbar_item_set_text(session, zathura->ui.statusbar.buffer, buffer);
    free(buffer);
  } else {
    girara_statusbar_item_set_text(session, zathura->ui.statusbar.buffer, "");
  }
}

void
cb_view_vadjustment_value_changed(GtkAdjustment *adjustment, gpointer data)
{
  zathura_t* zathura = data;
  if (!zathura || !zathura->document || !zathura->document->pages || !zathura->ui.page_view) {
    return;
  }

  /* get current adjustment values */
  gdouble lower = gtk_adjustment_get_value(adjustment);
  gdouble upper = lower + gtk_adjustment_get_page_size(adjustment);

  /* find page that fits */
  for (unsigned int page_id = 0; page_id < zathura->document->number_of_pages; page_id++)
  {
    zathura_page_t* page = zathura->document->pages[page_id];

    page_offset_t* offset = page_calculate_offset(page);
    if (offset == NULL) {
      continue;
    }

    double begin = offset->y;
    double end   = offset->y + page->height * zathura->document->scale;

    if (   ( (begin >= lower) && (end <= upper) ) /* [> page is in viewport <]*/
        || ( (begin <= lower) && (end >= lower) && (end <= upper) ) /* [> end of the page is in viewport <] */
        || ( (begin >= lower) && (end >= upper) && (begin <= upper) ) /* [> begin of the page is in viewport <] */
      ) {
      page->visible = true;
      if (page->surface == NULL) {
        render_page(zathura->sync.render_thread, page);
      }
    } else {
      page->visible = false;
      cairo_surface_destroy(page->surface);
      page->surface = NULL;
    }

    free(offset);
  }
}

void
cb_pages_per_row_value_changed(girara_session_t* UNUSED(session), const char* UNUSED(name), girara_setting_type_t UNUSED(type), void* value, void* data)
{
  g_return_if_fail(value != NULL);

  int pages_per_row = *(int*) value;
  zathura_t* zathura = data;

  if (pages_per_row < 1) {
    pages_per_row = 1;
  }

  page_view_set_mode(zathura, pages_per_row);
}

void
cb_index_row_activated(GtkTreeView* tree_view, GtkTreePath* path,
    GtkTreeViewColumn* UNUSED(column), void* data)
{
  zathura_t* zathura = data;
  if (tree_view == NULL || zathura == NULL || zathura->ui.session == NULL) {
    return;
  }

  GtkTreeModel  *model;
  GtkTreeIter   iter;

  g_object_get(tree_view, "model", &model, NULL);

  if(gtk_tree_model_get_iter(model, &iter, path))
  {
    zathura_index_element_t* index_element;
    gtk_tree_model_get(model, &iter, 2, &index_element, -1);

    if (index_element == NULL) {
      return;
    }

    if (index_element->type == ZATHURA_LINK_TO_PAGE) {
      sc_toggle_index(zathura->ui.session, NULL, 0);
      page_set_delayed(zathura, index_element->target.page_number);
    } else if (index_element->type == ZATHURA_LINK_EXTERNAL) {
      if (!girara_xdg_open(index_element->target.uri)) {
        girara_notify(zathura->ui.session, GIRARA_ERROR, "Failed to run xdg-open.");
      }
    }
  }

  g_object_unref(model);
}
