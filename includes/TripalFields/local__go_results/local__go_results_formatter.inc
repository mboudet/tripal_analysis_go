<?php
/**
 * @class
 * Purpose:
 *
 * Display:
 * Configuration:
 */
class local__go_results_formatter extends ChadoFieldFormatter {

  // The default label for this field.
  public static $default_label = 'Go results';

  // The list of field types for which this formatter is appropriate.
  public static $field_types = array('local__go_results');

  // The list of default settings for this formatter.
  public static $default_settings = array(
    'setting1' => 'default_value',
  );

   /**
    * @see ChadoFieldFormatter::settingsForm()
    *
    **/

  public function settingsForm($view_mode, $form, &$form_state) {

  }

    /**
    * @see ChadoFieldFormatter::View()
    *
    **/

  public function view(&$element, $entity_type, $entity, $langcode, $items, $display) {

    // Get the settings
    $settings = $display['settings'];

    $organism_id = $entity->chado_record->organism_id;

    // Check for permission to see Analysis entity

    $query = db_select('public.tripal_bundle', 'tb');
    $query->join('tripal_term', 'tt', 'tt.id = tb.term_id');
    $bundle_id = $query->fields('tb', ['name'])
      ->condition('tt.name', 'Analysis')
      ->execute()->fetchField();

    if(user_access('view ' . $bundle_id)){
      $form = drupal_get_form('tripal_analysis_go_select_form', $organism_id);
      $content = drupal_render($form);

     /*
      $content .= '<div id="tripal_analysis_go_org_charts"></div>';
      $content .= '<div id="tripal_cv_cvterm_info_box">';
      $content .= '<a href="#" onclick="jQuery("#tripal_cv_cvterm_info_box").hide(); return false;" style="float: right">Close [X]</a>';
      $content .= '<div>Term Information</div>';
      $content .= '<div id="tripal_cv_cvterm_info"></div></div>';
     */

      $content .= '
        <div id="tripal_analysis_go_org_charts"></div>
        <div id="tripal_cv_cvterm_info_box">
        <a href="#" onclick="jQuery(\'#tripal_cv_cvterm_info_box\').hide(); return false;" style="float: right">Close [X]</a>
        <div>Term Information</div>
        <div id="tripal_cv_cvterm_info"></div></div>
      ';
      $element[] = [
        '#type' => 'markup',
        '#markup' => $content,
      ];
    }
    return $element;

  }

    /**
    * @see ChadoFieldFormatter::settingsSummary()
    *
    **/

  public function settingsSummary($view_mode) {
    return '';
  }

}