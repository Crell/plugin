<?php

/**
 * Main interface for all component context objects.
 */
interface ComponentContextInterface {

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
 * Null implementation of component context.
 *
 * This is useful for components that do not have configuration.
 * @author lgarfiel
 *
 */
class ComponentContextNull implements ComponentContextInterface {

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
 * A base implementation of a component context object.
 */
abstract class ComponentContextBaseAbstract implements ComponentContextInterface {

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
