<?php

/**
 * Main interface for all component controllers.
 */
interface ComponentControllerInterface {

  /**
   * Constructor
   *
   * @param $type
   *   The component type this controller is managing.
   */
  public function __construct($type);

  /**
   * Load the component associated with the specified routing information.
   *
   * @param array $routing
   *   An associative array of values that will be used to determine which
   *   component is appropriate. The keys of the array are controller-dependent.
   * @return ComponentInterface
   */
  public function load(array $routing = array());

  /**
   * Attach the specified component and context with the specified routing information.
   *
   * @param  $component
   *   The internal name of the component.
   * @param ComponentContextInterface $context
   *   The context object to use for this component.
   * @param array $routing
   *   An array of routing information that should retrieve this component and
   *   context. The keys of the array are controller-dependent.
   * @return unknown_type
   */
  public function attach($component, ComponentContextInterface $context, array $routing = array());

  /**
   * Detach any specified component from the specified routing information.
   *
   * @param array $routing
   *   The routing information from which to remove any configured component.
   * @return unknown_type
   */
  public function detach(array $routing);

  /**
   * Set a default component to use if no other component resolves.
   *
   * @param $component
   *   The internal name of the component.
   * @param ComponentContextInterface $context
   *   The context object to use for this component.
   * @return unknown_type
   */
  public function setDefault($component, ComponentContextInterface $context);

  /**
   * Set default properties for a component.
   *
   * @param $info
   *   An associative array containing the properties specified by the
   *   corresponding info hook.  This method should modify this array in-place
   *   to set any appropriate defaults for unset values.
   */
  public function setComponentDefaults(&$info);
}


/**
 * Simple controller that uses single-axis routing.
 *
 * This controller can also be used for "no routing" component types by just
 * not specifying any routing information. Routing information is stored
 * to the variable system for fast lookup. Note that it is not well suited
 * for controllers with highly complex context objects as those will bloat
 * the variable table.
 */
class ComponentControllerVariable implements ComponentControllerInterface {

  /**
   * The component type this controller is managing.
   *
   * @var string
   */
  protected $componentType;

  /**
   * The info array for this component type.
   *
   * @var array
   */
  protected $typeInfo;

  public function __construct($type) {
    $this->componentType = $type;
    $this->typeInfo = component_type_get_info($type);
  }

  public function load(array $routing = array()) {

    $routing += array('key' => 'default');
    $variable = 'component_' . $this->componentType . '_' . $routing['key'];
    $component = variable_get($variable, NULL);
    if ($component) {
      list($component, $context) = $component;
      $context = unserialize($context);
      $component_info = component_get_info($this->componentType, $component);
      return new $component_info['class']($context, $component_info, $routing);
    }
    else {
      $component = $this->typeInfo['default'];
      $component_info = component_get_info($this->componentType, $component);
      $context = new $component_info['context'];
      return new $component_info['class']($context, $component_info, $routing);
    }
  }

  public function attach($component, ComponentContextInterface $context, array $routing = array()) {

  }

  public function detach(array $routing) {

  }

  public function setDefault($component, ComponentContextInterface $context) {

  }

  public function setComponentDefaults(&$info) {

  }

}

/**
 * Simple controller with single-axis routing that reuses controllers if available.
 *
 */
class ComponentControllerVariableReuse extends ComponentControllerVariable {

  /**
   * Cache of created components.
   *
   * @var array
   */
  protected $components = array();

  public function load(array $routing = array()) {
    $routing += array('key' => 'default');

    $key = $routing['key'];

    if (empty($this->components[$key])) {
      $this->components[$key] = parent::load($routing);
    }

    return $this->components[$key];
  }
}
