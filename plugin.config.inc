<?php

/**
 * Main interface for all plugin context objects.
 */
interface PluginContextInterface {

  /**
   * Define the available options for this context, and their defaults.
   *
   * @return array
   *   An associative array of options and their default values.
   */
  public function options();

  /**
   * Get the current value of the specified option.
   *
   * @param $option
   *    The option to retrieve.
   * @return
   *   The value of the option, or the default if not set.
   */
  public function getOption($option);

  /**
   * Set the specified option to a new value.
   *
   * @param $option
   *   The option for which to set a value.
   * @param $value
   *   The value to set.
   * @return unknown_type
   */
  public function setOption($option, $value);
}


/**
 * Null implementation of plugin context.
 *
 * This is useful for plugins that do not have configuration.
 * @author lgarfiel
 *
 */
class PluginContextNull implements PluginContextInterface {

  public function options() {
    return array();
  }

  public function getOption($option) {
    return NULL;
  }

  public function setOption($option, $value) {
    // This becomes a no-op.
  }
}

/**
 * A base implementation of a plugin context object.
 */
abstract class PluginContextBaseAbstract implements PluginContextInterface {

  /**
   * The options stored in this context object.
   *
   * @var array
   */
  protected $options = array();

  public function getOption($option) {
    if (!empty($this->options[$option])) {
      return $this->options[$option];
    }
    else {
      $options = $this->options();
      return $options[$option];
    }

  }

  public function setOption($option, $value) {
    $this->options[$option] = $value;
  }
}
